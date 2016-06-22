#include "icmpv6.h"

bool Icmpv6::parse(const u_char *pkt_data)
{
    auto hdr = reinterpret_cast<const icmp_header*>(pkt_data);

    _type = hdr->type;
    _code = hdr->code;
    child = nullptr;

    return true;
}

QString Icmpv6::type() const
{
    return "ICMPv6";
}

QString Icmpv6::src() const
{
    return parent->src();
}

QString Icmpv6::dst() const
{
    return parent->dst();
}

QString Icmpv6::description() const
{
    return QString("ICMPv6 Control Message");
}

QString Icmpv6::full_text() const
{
    QString str;
    str.append("ICMP Header:\n");
    QString type;
    switch(_type) {
    case 1:
        type = "Destination Unreachable"; break;
    case 2:
        type = "Packet Too Big"; break;
    case 3:
        type = "Time Exceeded"; break;
    case 4:
        type = "Parameter Problem"; break;
    case 128:
        type = "Echo Request"; break;
    case 129:
        type = "Echo Reply"; break;
    case 133:
        type = "Router Solicitation"; break;
    case 134:
        type = "Router Advertisement"; break;
    case 135:
        type = "Neighbor Solicitation"; break;
    case 136:
        type = "Neighbor Advertisement"; break;
    case 137:
        type = "Redirect Message"; break;
    default:
        type = "Depracated or Reserved"; break;
    }
    str.append(QString("  Type: %1\n").arg(type));
    str.append(QString("  Subtype: %1\n").arg(_code));

    if (child != nullptr)
        str.append(child->full_text());

    return str;
}
