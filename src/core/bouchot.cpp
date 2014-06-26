#include "core/bouchot.h"
#include <curl/curl.h>
#include <wx/sstream.h>
#include <wx/stdpaths.h>

bouchot::bouchot(wxString configFile)
{
    m_iNext = m_mData.begin();
    m_pConfigFile = new wxXmlDocument(configFile);
    wxXmlNode * TribuneNode     = m_pConfigFile->GetRoot(); //tribune
    wxXmlNode * UrlNode         = TribuneNode->GetChildren();
    wxXmlNode * IdentityNode    = UrlNode->GetNext();
    wxXmlNode * ColorsNode      = IdentityNode->GetNext();
    bool ok = m_ReTotoz.Compile("\\[\\:([a-zA-Z0-9\\ _]*)\\]");
    //m_ReNorloge.Compile("([01]?[0-9]|2[0-3]:[0-5][0-9]:[0-5][0-9]?\\^[0-9]|¹|²|³?)");
//    m_ReNorloge.Compile("{{{ (([01]?[0-9])|(2[0-3])):[0-5][0-9](:[0-5][0-9])?(\\^[0-9]|¹|²|³)?(@[0-9A-Za-z]+)? }}}");
    ok = m_ReNorloge.Compile("([0-2]{1}[0-9]{1}:[0-5]{1}[0-9]{1}:[0-5]{1}[0-9]{1})");

    m_sName         = TribuneNode->GetAttribute("name");
    m_sBaseUrl      = UrlNode->GetAttribute("base");
    m_sBackendUrl   = UrlNode->GetAttribute("backend");
    m_sPostUrl      = UrlNode->GetAttribute("post");
    m_sLogin        = IdentityNode->GetAttribute("login");
    m_sCookies      = IdentityNode->GetAttribute("cookie");
    m_sUserAgent    = IdentityNode->GetAttribute("useragent");
    m_sAnswerColor  = ColorsNode->GetAttribute("answer");
    m_sBgColor      = ColorsNode->GetAttribute("bg");
    m_sFgColor      = ColorsNode->GetAttribute("fg");
    m_sClockColor   = ColorsNode->GetAttribute("clock");
    m_sNorlogeColor = ColorsNode->GetAttribute("norloge");
    m_sLoginColor   = ColorsNode->GetAttribute("login");
    m_pIniManager   = new iniManager("./res/conf/config.ini");
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

void bouchot::sendPost(wxString connerie)
{
    CURL *                  curl;
    CURLcode                res;
    struct curl_httppost *  formpost=NULL;
    struct curl_httppost *  lastptr=NULL;
//    struct curl_slist *     headerlist=NULL;
    //static const char       buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    char * data = strdup(connerie.ToStdString().c_str());
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "message",
                 CURLFORM_COPYCONTENTS, data,
                 CURLFORM_END);


    curl = curl_easy_init();
  //  headerlist = curl_slist_append(headerlist, buf);
    if(curl)
    {
        char * url = strdup(wxString(m_sBaseUrl + "/" + m_sPostUrl).ToStdString().c_str());
        char * ua = strdup(m_sUserAgent.ToStdString().c_str());
        wxString proxy = m_pIniManager->getParam("proxy");
        wxString proxyPort = m_pIniManager->getParam("proxyPort");
        long port = 80;
        proxyPort.ToLong(&port);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_PROXY, proxy.ToStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
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
    //    curl_slist_free_all (headerlist);
    }
}

struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t WriteFileCallback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);

    return written;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL)
  {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


void bouchot::refresh()
{
    CURL *                  curl;
    CURLcode                res;
    struct curl_httppost *  lastptr=NULL;
    struct MemoryStruct     chunk;

    chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl)
    {
        wxString proxy = m_pIniManager->getParam("proxy");
        wxString proxyPort = m_pIniManager->getParam("proxyPort");
        long port = 80;
        proxyPort.ToLong(&port);
        char * url = strdup(wxString(m_sBaseUrl + "/" + m_sBackendUrl).ToStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_PROXY, proxy.ToStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_easy_setopt(curl, CURLOPT_URL, url);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(res));

        wxString tmp = wxString::FromUTF8(chunk.memory,  chunk.size);
        wxStringInputStream *httpStream = new wxStringInputStream(tmp);

        //if (httpStream->GetSize() != 0)
        {
            // will crash here, if xml content is not formatted PERFECTLY
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
                                if (!wxDir::Exists("/tmp/totoz"))
                                {
                                    wxDir::Make("/tmp/totoz");
                                }
                                //wxString tmpPath = wxStandardPaths::GetTempDir();
                                wxString tmp = m_ReTotoz.GetMatch(message, 1);
                                wxString source = "http://totoz.eu/img/" + tmp;
                                wxString dest = "/tmp/totoz/" + tmp;
                                if (!wxFileExists(dest))
                                {
                                    FILE *fp;
                                    fp = fopen(dest.ToStdString().c_str(), "w+");

                                    char * url = strdup(source.ToStdString().c_str());
                                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteFileCallback);
                                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
                                    curl_easy_setopt(curl, CURLOPT_PROXY, proxy.ToStdString().c_str());
                                    curl_easy_setopt(curl, CURLOPT_PROXYPORT, port);
                                    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
                                    curl_easy_setopt(curl, CURLOPT_URL, url);

                                    res = curl_easy_perform(curl);
                                    if(res != CURLE_OK)
                                        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                                    curl_easy_strerror(res));
                                    fclose(fp);
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
        //else
            //wxMessageBox(_T("Can't connect!"));
        if (firstCall)
        {
            m_iNext = m_mData.begin();
            firstCall = false;
        }
        wxDELETE(httpStream);
        curl_easy_cleanup(curl);
    }
}
