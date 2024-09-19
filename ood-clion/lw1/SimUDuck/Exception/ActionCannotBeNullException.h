#pragma once

#include <exception>
#include <iostream>
#include <string>

class ActionCannotBeNullException : public std::exception
{
public:
	ActionCannotBeNullException()
		: m_message("action can't be null")
	{
	}

	const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:
	std::string m_message;
};