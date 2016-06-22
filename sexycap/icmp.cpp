#include "icmp.h"
#include "protocols.h"

bool Icmp::parse(const u_char* pkt_data)
{
    auto hdr = reinterpret_cast<const icmp_header*>(pkt_data);

    _type = hdr->type;
    _code = hdr->code;
    child = nullptr;

    return true;
}

QString Icmp::type() const
{
    return "ICMP";
}

QString Icmp::src() const
{
    return parent->src();
}

QString Icmp::dst() const
{
    return parent->dst();
}

QString Icmp::description() const
{
    return QString("ICMP Control Message");
}

QString Icmp::full_text() const
{
    QString str;
    str.append("ICMP Header:\n");
    QString type;
    switch(_type) {
    case 0:
        type = "Echo Reply"; break;
    case 3:
        type = "Destination Unreachable"; break;
    case 4:
        type = "Source Quench"; break;
    case 5:
        type = "Redirect Message"; break;
    case 8:
        type = "Echo Request"; break;
    case 9:
        type = "Router Advertisement"; break;
    case 10:
        type = "Router Solicitation"; break;
    case 11:
        type = "Time Exceeded"; break;
    case 12:
        type = "Parameter Problem: Bad IP header"; break;
    case 13:
        type = "Timestamp"; break;
    case 14:
        type = "Timestamp Reply"; break;
    default:
        type = "Depracated or Reserved"; break;
    }
    str.append(QString("  Type: %1\n").arg(type));
    str.append(QString("  Subtype: %1\n").arg(_code));

    if (child != nullptr)
        str.append(child->full_text());

    return str;
}
