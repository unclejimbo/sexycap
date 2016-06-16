#include "dns.h"
#include "protocols.h"

bool Dns::parse(const u_char* pkt_data)
{
    auto hdr = reinterpret_cast<const dns_header*>(pkt_data);

    _id = ntohs(hdr->id);
    auto flags = ntohs(hdr->flags);
    _qr = flags & 0x8000;
    _opcode = flags & 0x7800;
    _aa = flags & 0x0400;
    _tc = flags & 0x0200;
    _rd = flags & 0x0100;
    _ra = flags & 0x0080;
    _rcode = flags & 0x000f;
    _nq = ntohs(hdr->nq);
    _na = ntohs(hdr->na);
    _nauth_rrs = ntohs(hdr->nauth_rrs);
    _naddt_rrs = ntohs(hdr->naddt_rrs);

    if (_qr == 0) { // question
        auto q = reinterpret_cast<const dns_question*>(pkt_data + 12);
        _qname = ntohl(q->qname);
        _qtype = ntohl(q->qtype);
        _qclass = ntohl(q->qclass);
    } else { // answer

    }

    child = nullptr;
    return true;
}

QString Dns::type() const
{
    return "DNS";
}

QString Dns::src() const
{
    return parent->src();
}

QString Dns::dst() const
{
    return parent->dst();
}

QString Dns::description() const
{
    if (_qr == 0)
        return QString("DNS ask for ").append(_qname);
    else
        return QString("DNS answer");
}

QString Dns::full_text() const
{
    QString str;
    str.append("DNS Header:\n");
    str.append(QString("  Identification: %1\n").arg(_id));
    if (_qr == 0)
        str.append("  Message Type: Question\n");
    else
        str.append("  Message Type: Answer\n");
    switch(_opcode) {
    case 1:
        str.append("  Response Type: Standard\n");
        break;
    case 2:
        str.append("  Response Type: Reverse\n");
        break;
    case 3:
        str.append("  Response Type: Server Status\n");
        break;
    default:
        break;
    }
    str.append(QString("  Authority Answer: %1\n").arg(_aa));
    str.append(QString("  Truncated: %1\n").arg(_tc));
    str.append(QString("  Recursive Demand: %1\n").arg(_rd));
    str.append(QString("  Recursive Answer: %1\n").arg(_ra));
    str.append(QString("  Number of Questions: %1\n").arg(_nq));
    str.append(QString("  Number of Answers: %1\n").arg(_na));
    str.append(QString("  Number of Authority Answers: %1\n").arg(_nauth_rrs));
    str.append(QString("  Number of Additional Answers: %1\n").arg(_naddt_rrs));

    return str;
}
