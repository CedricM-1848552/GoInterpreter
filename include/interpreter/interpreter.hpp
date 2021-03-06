#ifndef GOINTERPRETER_INTERPRETER_INTERPRETER_HPP
#define GOINTERPRETER_INTERPRETER_INTERPRETER_HPP

#include <iostream>

#include "ast/visitor.hpp"
#include "interpreter/values.hpp"
#include "utils/stack.hpp"
#include "validation/symbol_table.hpp"

class Interpreter : public AST::Visitor
{
public:
    Interpreter();
    ~Interpreter();

    // Program
    void visitProgram(long size) override;

    // Types
    void visitBoolType() override;
    void visitIntType() override;
    void visitFloat32Type() override;
    void visitRuneType() override;
    void visitStringType() override;
    void visitArrayType(long size) override;
    void visitSliceType() override;
    void visitStructType(std::vector<std::string> fields) override;
    void visitPointerType() override;
    void visitFunctionType(std::vector<std::string> parameters, std::vector<std::string> returns) override;
    void visitMapType() override;
    void visitCustomType(std::string id) override;

    // Block
    void visitBlock(const std::vector<const std::function<void ()>> visitStatements) override;

    // Declarations
    void visitFunctionDeclaration(std::string id, const std::function<void ()>& visitSignature, const std::function<void ()>& visitBody) override;
    void visitTypeAliasDeclaration(std::string id) override;
    void visitTypeDefinitionDeclaration(std::string id) override;
    void visitVariableDeclaration(std::vector<std::string> ids, bool typeDeclared, long expression_count) override;

    // Statements
    void visitExpressionStatement() override;
    void visitAssignmentStatement(const std::function<long ()>& visitLhs, const std::function<long ()>& visitRhs) override;
    void visitIfStatement(const std::function <void ()>& visitTrue, const std::function <void ()>& visitFalse) override;
    void visitSwitchStatement(const std::function<void ()>& visitExpression, const std::vector<const std::function<void ()>> visitClauses) override;
    void visitSwitchExpressionClause(const std::vector<const std::function<void ()>> visitExpressions, const std::vector<const std::function<void ()>> visitStatements) override;
    void visitSwitchDefaultClause(const std::vector<const std::function<void ()>> visitStatements) override;
    void visitReturnStatement(long size) override;
    void visitBreakStatement() override;
    void visitContinueStatement() override;
    void visitEmptyStatement() override;
    void visitForConditionStatement(const std::function<void ()>& visitInit, const std::function<void ()>& visitCondition, const std::function<void ()>& visitPost, const std::function<void ()>& visitBody) override;

    // Expressions - Literals
    void visitBoolExpression(bool value) override;
    void visitIntExpression(int value) override;
    void visitFloat32Expression(float value) override;
    void visitRuneExpression(char value) override;
    void visitStringExpression(char *value, long length) override;

    // Expressions - Rest
    void visitIdentifierExpression(std::string id) override;
    void visitCompositLiteralExpression(std::vector<std::string> keys) override;
    void VisitFunctionLiteralExpression(const std::function<void ()>& visitSignature, const std::function<void ()>& visitBody) override;
    void visitSelectExpression(std::string id) override;
    void visitIndexExpression() override;
    void visitSimpleSliceExpression(bool lowDeclared, bool highDeclared) override;
    void visitFullSliceExpression(bool lowDeclared) override;
    void visitCallExpression(long size) override;
    void visitConversionExpression() override;
    void visitUnaryPlusExpression() override;
    void visitUnaryNegateExpression() override;
    void visitUnaryLogicalNotExpression() override;
    void visitUnaryBitwiseNotExpression() override;
    void visitUnaryDereferenceExpression() override;
    void visitUnaryReferenceExpression() override;
    void visitBinaryLogicalOrExpression() override;
    void visitBinaryLogicalAndExpression() override;
    void visitBinaryEqualExpression() override;
    void visitBinaryNotEqualExpression() override;
    void visitBinaryLessThanExpression() override;
    void visitBinaryLessThanEqualExpression() override;
    void visitBinaryGreaterThanExpression() override;
    void visitBinaryGreaterThanEqualExpression() override;
    void visitBinaryShiftLeftExpression() override;
    void visitBinaryShiftRightExpression() override;
    void visitBinaryAddExpression() override;
    void visitBinarySubtractExpression() override;
    void visitBinaryBitwiseOrExpression() override;
    void visitBinaryBitwiseXOrExpression() override;
    void visitBinaryBitwiseAndExpression() override;
    void visitBinaryMultiplyExpression() override;
    void visitBinaryDivideExpression() override;
    void visitBinaryModuloExpression() override;

private:
    enum class CompositeLiteralType {
        Struct,
        Slice,
        Array,
    };

    Stack<Value *> stack;
    Stack<Value *> switchStack;
    SymbolTable<Value *> symbolTable;

    Stack<long> returnsByCurrentFunction;
    Stack<bool> functionClosed;
    Stack<CompositeLiteralType> compositeLiteralType;

    bool cont;
    bool brk;
    bool ret;
};

#endif // GOINTERPRETER_INTERPRETER_INTERPRETER_HPP
