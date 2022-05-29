#include "Component.h"
size_t BaseComponentType::assignId(){ return m_sIdCount++;};
size_t BaseComponentType::m_sIdCount = 0;