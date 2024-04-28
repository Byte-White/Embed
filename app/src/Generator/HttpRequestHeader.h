const char* HttpRequestHeaderEmbed = R"(
#include <WiFi.h>
#include <map>

class HttpRequest
{
  public:
  HttpRequest();
  void reset();

  void process(Client& client);

  String get(String header);
  String set(String header, String value);
  
  void setMetod(String method) { m_Method = method; }
  void setRequestedResource(String req) { m_RequestedResource = req; }
  void setHttpVersion(String ver) { m_HttpVersion = ver; }
  void setBody(const String& body) { m_Body = body; }

  inline const String& getMethod() { return m_Method; }
  inline const String& getRequestedResource() { return m_RequestedResource; }
  inline const String& getHttpVersion() { return m_HttpVersion; }
  inline const String& getBody() { return m_Body; }

  inline const String& getHost() { return get("Host"); }
  inline const String& getUserAgent() { return get("User-Agent"); }
  inline const String& getAccept() { return get("Accept"); }
  inline const String& getAcceptLanguage() { return get("Accept-Language"); }
  inline const String& getAcceptEncoding() { return get("Accept-Encoding"); }
  inline const String& getConnection() { return get("Connection"); }  

  String to_string();

  private:
  void parseHeader(const String& header);
  
  String m_Method, m_RequestedResource, m_HttpVersion;
  std::map<String,String> m_Headers;
  String m_Body;
};
)"