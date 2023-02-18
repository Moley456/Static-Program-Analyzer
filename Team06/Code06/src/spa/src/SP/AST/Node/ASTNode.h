#pragma once

#include "../Visitor/ASTVisitor.h"
#include <memory>
#include <string>

// interface for ASTNodes 
class ASTNode {
public:
	virtual void accept(ASTVisitor* visitor) = 0;
};