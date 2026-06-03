#include "slotexception.h"

SlotException::SlotException(std::string plaats, std::string id)
    : m_plaats(std::move(plaats)), m_id(std::move(id))
{
    m_fullMessage = "Fout bij slot '" + m_plaats + "' veroorzaakt door ID: " + m_id;
}

const char* SlotException::what() const noexcept
{
    return m_fullMessage.c_str();
}

std::string SlotException::getPlaats() const
{
    return m_plaats;
}

std::string SlotException::getId() const
{
    return m_id;
}