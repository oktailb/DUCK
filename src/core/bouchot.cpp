#include "core/bouchot.h"
#include <curl/curl.h>

bouchot::bouchot(wxString configFile)
{
    m_iNext = m_mData.begin();
    m_pConfigFile = new wxXmlDocument(configFile);
    wxXmlNode * TribuneNode     = m_pConfigFile->GetRoot(); //tribune
    wxXmlNode * UrlNode         = TribuneNode->GetChildren();
    wxXmlNode * IdentityNode    = UrlNode->GetNext();
    wxXmlNode * ColorsNode      = IdentityNode->GetNext();
    bool ok = m_ReTotoz.Compile("\\[\\:([a-zA-Z0-9\\ \\:_]*)\\]");
    //m_ReNorloge.Compile("([01]?[0-9]|2[0-3]:[0-5][0-9]:[0-5][0-9]?\\^[0-9]|¹|²|³?)");
//    m_ReNorloge.Compile("{{{ (([01]?[0-9])|(2[0-3])):[0-5][0-9](:[0-5][0-9])?(\\^[0-9]|¹|²|³)?(@[0-9A-Za-z]+)? }}}");
    ok = m_ReNorloge.Compile("([0-2]{1}[0-9]{1}:[0-5]{1}[0-9]{1}:[0-5]{1}[0-9]{1})");

    m_sName         = TribuneNode->GetAttribute("name");
    m_sBaseUrl      = UrlNode->GetAttribute("base");
    m_sBackendUrl   = UrlNode->GetAttribute("backend");
    m_sPostUrl      = UrlNode->GetAttribute("post");
    m_sPostData     = UrlNode->GetAttribute("data");
    m_sLogin        = IdentityNode->GetAttribute("login");
    m_sCookies      = IdentityNode->GetAttribute("cookie");
    m_sUserAgent    = IdentityNode->GetAttribute("useragent");
    m_sAnswerColor  = ColorsNode->GetAttribute("answer");
    m_sBgColor      = ColorsNode->GetAttribute("bg");
    m_sFgColor      = ColorsNode->GetAttribute("fg");
    m_sClockColor   = ColorsNode->GetAttribute("clock");
    m_sNorlogeColor = ColorsNode->GetAttribute("norloge");
    m_sLoginColor   = ColorsNode->GetAttribute("login");
    firstCall = true;
}

bouchot::~bouchot()
{
    delete m_pConfigFile;
}

int64_t bouchot::getNextPost(t_post &ret)
{
    m_iNext++;
    if (m_iNext == m_mData.end())
    {
        m_iNext--;
        return -1;
    }
    m_iNext->second.used = true;
    ret = m_iNext->second;
    return m_iNext->first;
}

static void
print_cookies(CURL *curl)
{
  CURLcode res;
  struct curl_slist *cookies;
  struct curl_slist *nc;
  int i;

  printf("Cookies, curl knows:\n");
  res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);
  if (res != CURLE_OK) {
    fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n", curl_easy_strerror(res));
    exit(1);
  }
  nc = cookies, i = 1;
  while (nc) {
    printf("[%d]: %s\n", i, nc->data);
    nc = nc->next;
    i++;
  }
  if (i == 1) {
    printf("(none)\n");
  }
  curl_slist_free_all(cookies);
}

void bouchot::sendPost(wxString connerie)
{
    CURL * curl;
    CURLcode res;
    struct curl_httppost * formpost=NULL;
    struct curl_httppost * lastptr=NULL;
// struct curl_slist * headerlist=NULL;
    //static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    char * data = strdup(connerie.ToStdString().c_str());
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "message",
                 CURLFORM_COPYCONTENTS, data,
                 CURLFORM_END);


    curl = curl_easy_init();
  // headerlist = curl_slist_append(headerlist, buf);
    if(curl)
    {
        char * url = strdup(wxString(m_sBaseUrl + "/" + m_sPostUrl).ToStdString().c_str());
        char * ua = strdup(m_sUserAgent.ToStdString().c_str());
        char * cookie = strdup(m_sCookies.ToStdString().c_str());
//        curl_easy_escape(curl , url , 0);
  //      curl_easy_escape(curl , ua , 0);
        cookie = strdup(curl_easy_escape(curl , cookie , 0));
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); /* just to start the cookie engine */
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
        res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, cookie);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "Curl curl_easy_setopt failed: %s\n", curl_easy_strerror(res));
            return;
        }

        print_cookies(curl);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, ua);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        curl_formfree(formpost);
        //free(url);
        //free(ua);
    // curl_slist_free_all (headerlist);
    }
}

void bouchot::refresh()
{
    wxURL * myUrl = new wxURL();
    myUrl->SetURL("http://" + m_sBaseUrl + "/" +  m_sBackendUrl);

    wxInputStream *httpStream = myUrl->GetInputStream();

    if (myUrl->GetError() != wxURL_PROTOERR)
    {
        // will crash here, if xml content is not formatted PERFECTLY
        try
        {
            wxXmlDocument xml(*httpStream);

            wxString    autor;
            wxString    message;
            wxString    info;
            wxString    date;
            uint64_t    id;
            wxXmlNode * node = xml.GetRoot()->GetChildren();
            while (node)
            {
                if (node->GetName() == _T("post"))
                {
                    node->GetAttribute("id").ToCULong(&id);
                    date = node->GetAttribute("time");
                    wxXmlNode * post = node->GetChildren();
                    while (post)
                    {
                        if (post->GetName() == "info")
                        {
                            info = post->GetNodeContent();
                        }
                        else if (post->GetName() == "message")
                        {
                            message = post->GetNodeContent();
                            while (m_ReTotoz.Matches(message))
                            {
                                wxString tmp = m_ReTotoz.GetMatch(message, 1);
                                wxString source = "http://totoz.eu/img/" + tmp;
                                wxString dest = "/tmp/totoz/" + tmp;
                                if (!wxFileExists(dest))
                                {
                                    wxURL * nimage = new wxURL(source);
                                    wxInputStream *nimageStream = nimage->GetInputStream();

                                    if (nimage->GetError() != wxURL_PROTOERR)
                                    {
                                        if (!wxDir::Exists("/tmp/totoz"))
                                        {
                                            wxDir::Make("/tmp/totoz");
                                        }
                                        wxFile destFile;
                                        destFile.Create(dest);
                                        void * buffer = malloc(nimageStream->GetSize());
                                        nimageStream->Read(buffer, nimageStream->GetSize());
                                        destFile.Write(buffer, nimageStream->GetSize());
                                        destFile.Close();
                                        free(buffer);
                                    }
                                }
                                m_ReTotoz.ReplaceFirst(&message, "<img src='/tmp/totoz/\\1'>");
                            }
                            if (m_ReNorloge.Matches(message))
                            {
                                //wxString test = m_ReTotoz.GetMatch(message, 1);
                                size_t count = m_ReNorloge.ReplaceAll(&message, "<a href='norloge_\\1'>\\1</a>");
                                //count = count;
                            }
                        }
                        else if (post->GetName() == "login")
                        {
                            autor = post->GetNodeContent();
                        }
                        post = post->GetNext();
                    }
                    t_post tmp = {false, info, date, autor, message};
                    m_mData.insert(std::make_pair<uint64_t, t_post>(id, tmp));
                }
                node = node->GetNext();
            }
        }
        catch (...)
        {
            // coupure de connexion ou mise en veille bien souvent
        }
    }
    //else
        //wxMessageBox(_T("Can't connect!"));
    if (firstCall)
    {
        m_iNext = m_mData.begin();
        firstCall = false;
    }
    wxDELETE(httpStream);
}
