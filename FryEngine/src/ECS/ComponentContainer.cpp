#include "ComponentContainer.h"
size_t BaseComponentContainer::assignId(){ return m_sIdCount++;};
size_t BaseComponentContainer::m_sIdCount = 0;