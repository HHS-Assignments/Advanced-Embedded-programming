#ifndef SLOTEXCEPTION_H
#define SLOTEXCEPTION_H

#include <string>
#include <exception>

class SlotException : public std::exception
{
public:
    SlotException(std::string plaats, std::string id);
    virtual ~SlotException() = default;

    const char* what() const noexcept override;
    std::string getPlaats() const;
    std::string getId() const;

private:
    std::string m_plaats;
    std::string m_id;
    mutable std::string m_fullMessage;
};

#endif // SLOTEXCEPTION_H