#ifndef GOINTERPRETER_AST_STATEMENTS_HPP
#define GOINTERPRETER_AST_STATEMENTS_HPP

#include "ast/base.hpp"

namespace AST {

    class DeclarationStatement : public Statement 
    {
    public:
        DeclarationStatement(Declaration *declaration);
        virtual ~DeclarationStatement() override;
        virtual void accept(Visitor *visitor) const override;

    private:
        Declaration *declaration;
    };

    class ExpressionStatement : public SimpleStatement 
    {
    public:
        ExpressionStatement(Expression *expression);
        virtual ~ExpressionStatement() override;
        virtual void accept(Visitor *visitor) const override;

    private:
        Expression *expression;
    };

    class AssignmentStatement : public SimpleStatement
    {
    public:
        AssignmentStatement(std::vector<Expression *> lhs, std::vector<Expression *> rhs);
        virtual ~AssignmentStatement() override;
        virtual void accept(Visitor *visitor) const override;

    private:
        std::vector<Expression *> lhs;
        std::vector<Expression *> rhs;
    };

    class IfStatement : public Statement
    {
    public:
        IfStatement(Expression *condition, Block *trueBody, Block *falseBody);
        virtual ~IfStatement() override;
        virtual void accept(Visitor *visitor) const override;

    private:
        Expression *condition;
        Block *trueBody;
        Block *falseBody;
    };

    class SwitchStatement : public Statement 
    {
    public:
        class SwitchClause
        {
        protected:
            SwitchClause() = default;

        public:
            virtual ~SwitchClause() = default;
            virtual void accept(Visitor *visitor) const = 0;
        };

        class SwitchExpressionClause : public SwitchClause
        {
        private:
            std::vector<Expression *> expressions;
            std::vector<Statement *> statements;

        public:
            SwitchExpressionClause(std::vector<Expression *> expressions, std::vector<Statement *> statements);
            ~SwitchExpressionClause();
            void accept(Visitor *visitor) const override;
        };

        class SwitchDefaultClause : public SwitchClause
        {
        private:
            std::vector<Statement *> statements;

        public:
            SwitchDefaultClause(std::vector<Statement *> statements);
            ~SwitchDefaultClause();
            void accept(Visitor *visitor) const override;
        };

        SwitchStatement(Expression *expression, std::vector<SwitchClause *> clauses);
        virtual ~SwitchStatement() override;
        virtual void accept(Visitor *visitor) const override;

    private:
        Expression *expression;
        std::vector<SwitchClause *> clauses;
    };

    class ReturnStatement : public Statement 
    {
    public:
        ReturnStatement(std::vector<Expression *> expressions);
        virtual ~ReturnStatement() override;
        virtual void accept(Visitor* visitor) const override;

    private:
        std::vector<Expression *> expressions;
    };

    class BreakStatement : public Statement
    {
    public:
        BreakStatement() = default;
        virtual ~BreakStatement() override = default;
        virtual void accept(Visitor *visitor) const override;
    };

    class ContinueStatement : public Statement
    {
    public:
        ContinueStatement() = default;
        virtual ~ContinueStatement() override = default;
        virtual void accept(Visitor *visitor) const override;
    };

    class EmptyStatement : public SimpleStatement
    {
    public:
        EmptyStatement() = default;
        virtual ~EmptyStatement() override = default;
        virtual void accept(Visitor *visitor) const override;
    };

    class ForConditionStatement : public Statement
    {
    public:
        ForConditionStatement(SimpleStatement *init, Expression *condition, SimpleStatement *post, Block *body);
        virtual ~ForConditionStatement() override;
        virtual void accept(Visitor *visitor) const override;
    
    private:
        SimpleStatement *init;
        Expression *condition;
        SimpleStatement *post;
        Block *body;
    };

};

#endif // GOINTERPRETER_AST_STATEMENTS_HPP