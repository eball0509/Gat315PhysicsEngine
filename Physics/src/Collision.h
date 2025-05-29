#pragma once
#include "World.h"

void CreateContacts(const bodies_t& bodies, contacts_t& contacts);

void SeparateContacts(contacts_t& contacts);