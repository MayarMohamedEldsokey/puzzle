#include "user_model.h"

UserModel::UserModel()
    : m_email(""), m_username(""), m_userId("")
{
}

void UserModel::clear()
{
    m_email = "";
    m_username = "";
    m_userId = "";
}
