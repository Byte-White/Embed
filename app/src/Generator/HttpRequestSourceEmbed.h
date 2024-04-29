const char* HttpRequestSourceEmbed = R"(
#include "HttpRequest.h"

int split(const String& str, const String& delim, String* parts, int maxParts)
{
    int count = 0;
    int start = 0;
    int end = str.indexOf(delim);

    while (end != -1 && count < maxParts) {
        parts[count++] = str.substring(start, end);
        start = end + delim.length();
        end = str.indexOf(delim, start);
    }

    if (count < maxParts) {
        parts[count++] = str.substring(start);
    }

    return count;
}



HttpRequest::HttpRequest()
{
    reset();
}

void HttpRequest::reset()
{
    m_Method = "";
    m_RequestedResource = "";
    m_HttpVersion = "";
    m_Body = "";
    m_Headers.clear();
}


void HttpRequest::process(Client& client)
{
    String request = "";
    while (client.available())
    {
        char c = client.read();
        request += c;

        if (request.endsWith("\r\n\r\n"))
        {
            break;
        }
    }

    String headerPart = request.substring(0, request.indexOf("\r\n\r\n")); // removes the last \r\n

    parseHeader(headerPart);

    // Body

    String body = "";
    while (client.available())
    {
        char c = client.read();
        body += c;

        if (request.endsWith("\r\n\r\n"))
        {
            break;
        }
    }

    setBody(request);
}

void HttpRequest::parseHeader(const String& header)
{
    String lines[20];
    int numLines = split(header, "\r\n", lines, 20);


    for (int i = 1; i < numLines; i++) // i = 1 -> Skip the start-line
    {
        String line = lines[i];
        int separatorIndex = line.indexOf(':');
        if (separatorIndex != -1)
        {
            String headerName = line.substring(0, separatorIndex);
            String headerValue = line.substring(separatorIndex + 2); // Skipping ": "

            m_Headers[headerName] = headerValue;
        }
    }

    m_Method = lines[0].substring(0, lines[0].indexOf(' '));

    int firstSpaceIndex = lines[0].indexOf(' ') + 1;
    int secondSpaceIndex = lines[0].indexOf(' ', firstSpaceIndex);
    m_RequestedResource = lines[0].substring(firstSpaceIndex, secondSpaceIndex);

    int httpVersionStart = lines[0].lastIndexOf("HTTP/") + 5;
    int httpVersionEnd = lines[0].indexOf("\r\n", httpVersionStart);
    m_HttpVersion = lines[0].substring(httpVersionStart, httpVersionEnd);
}

String HttpRequest::get(String header)
{
    if (m_Headers.find(header) != m_Headers.end()) return m_Headers[header];
    else return "";
}

String HttpRequest::set(String header, String value)
{
    m_Headers[header] = value;
}

String HttpRequest::to_string()
{
    String result = "";

    for (auto const& header : m_Headers)
    {
        result += header.first + ": " + header.second + "\r\n";
    }

    result += "\r\n";

    if (!m_Body.isEmpty()) result += m_Body;

    result += "\r\n";

    return result;
}
)";