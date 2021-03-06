#include "ast/types.hpp"

void AST::BoolType::accept(Visitor *visitor) const
{
    visitor->visitBoolType();
}

void AST::IntType::accept(Visitor *visitor) const
{
    visitor->visitIntType();
}

void AST::Float32Type::accept(Visitor *visitor) const
{
    visitor->visitFloat32Type();
}

void AST::RuneType::accept(Visitor *visitor) const
{
    visitor->visitRuneType();
}

void AST::StringType::accept(Visitor *visitor) const
{
visitor->visitStringType();
}

AST::ArrayType::ArrayType(long size, Type *type)
    :type{type}, size{size} 
{}

AST::ArrayType::~ArrayType()
{
    delete this->type;
}

void AST::ArrayType::accept(Visitor *visitor) const
{
    this->type->accept(visitor);
    visitor->visitArrayType(this->size);
}

AST::SliceType::SliceType(Type *type)
    :type{type}
{}

AST::SliceType::~SliceType()
{
    delete this->type;
}

void AST::SliceType::accept(Visitor *visitor) const
{
    this->type->accept(visitor);
    visitor->visitSliceType();
}

AST::StructType::StructType(std::vector<std::pair<std::string, Type *>> fields)
    :fields{fields}
{}

AST::StructType::~StructType()
{
    for (const auto pair : this->fields) {
        delete pair.second;
    }
}

void AST::StructType::accept(Visitor *visitor) const
{
    std::vector<std::string> field_names;
    std::vector<Type *> field_types;

    for (const auto pair : this->fields) {
        field_names.push_back(pair.first);
        field_types.push_back(pair.second);
    }

    for (const auto type : field_types) {
        type->accept(visitor);
    }

    visitor->visitStructType(field_names);
}

AST::PointerType::PointerType(Type *type)
    :type{type}
{}

AST::PointerType::~PointerType()
{
    delete this->type;
}

void AST::PointerType::accept(Visitor *visitor) const
{
    this->type->accept(visitor);
    visitor->visitPointerType();
}

AST::FunctionType::FunctionType(
    std::vector<std::pair<std::string, Type *>> parameters, 
    std::vector<std::pair<std::string, Type *>> returns)
    :parameters{parameters}, returns{returns}
{}

AST::FunctionType::~FunctionType()
{
    for (const auto ppair : this->parameters) {
        delete ppair.second;
    }

    for (const auto rpair : this->returns) {
        delete rpair.second;
    }
}

void AST::FunctionType::accept(Visitor *visitor) const
{
    std::vector<std::string> parameter_names;
    std::vector<Type *> parameter_types;

    for (const auto ppair : this->parameters) {
        parameter_names.push_back(ppair.first);
        parameter_types.push_back(ppair.second);
    }

    for (const auto type : parameter_types) {
        type->accept(visitor);
    }

    std::vector<std::string> return_names;
    std::vector<Type *> return_types;

    for (const auto rpair : this->returns) {
        return_names.push_back(rpair.first);
        return_types.push_back(rpair.second);
    }

    for (const auto type : return_types) {
        type->accept(visitor);
    }

    visitor->visitFunctionType(parameter_names, return_names);
}

AST::MapType::MapType(Type *keyType, Type *elementType)
    :keyType{keyType}, elementType{elementType}
{}

AST::MapType::~MapType()
{
    delete keyType;
    delete elementType;
}

void AST::MapType::accept(Visitor *visitor) const
{
    this->keyType->accept(visitor);
    this->elementType->accept(visitor);
    visitor->visitMapType();
}

AST::CustomType::CustomType(const char *id)
    :id{std::string{id}} 
{}

void AST::CustomType::accept(Visitor *visitor) const
{
    visitor->visitCustomType(this->id);
}