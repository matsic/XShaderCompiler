/*
 * HLSLParser.h
 * 
 * This file is part of the "HLSL Translator" (Copyright (c) 2014 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef HTLIB_HLSL_PARSER_H
#define HTLIB_HLSL_PARSER_H


#include "HT/Log.h"
#include "HLSLScanner.h"
#include "Parser.h"
#include "Visitor.h"
#include "Token.h"

#include <vector>
#include <map>
#include <string>


namespace HTLib
{


// Syntax parser class.
class HLSLParser : public Parser
{
    
    public:
        
        HLSLParser(const Options& options, Log* log = nullptr);

        ProgramPtr ParseSource(const std::shared_ptr<SourceCode>& source);

    private:
        
        /* === Enumerations === */

        // Variable declaration modifiers.
        enum class VarModifiers
        {
            // Storage class or interpolation modifier (extern, linear, centroid, nointerpolation, noperspective, sample).
            StorageModifier,

            // Type modifier (const, row_major, column_major).
            TypeModifier,
        };

        /* === Functions === */

        Scanner& GetScanner() override;

        // Accepts the semicolon token (Accept(Tokens::Semicolon)).
        void Semi();

        // Returns true if the current token is a data type.
        bool IsDataType() const;
        
        // Returns true if the current token is a literal.
        bool IsLiteral() const;

        // Returns true if the current token is part of a primary expression.
        bool IsPrimaryExpr() const;

        /* === Parse functions === */

        ProgramPtr                      ParseProgram();

        CodeBlockPtr                    ParseCodeBlock();
        BufferDeclIdentPtr              ParseBufferDeclIdent();
        FunctionCallPtr                 ParseFunctionCall(VarIdentPtr varIdent = nullptr);
        StructurePtr                    ParseStructure();
        VarDeclStmntPtr                 ParseParameter();
        SwitchCasePtr                   ParseSwitchCase();

        GlobalDeclPtr                   ParseGlobalDecl();
        FunctionDeclPtr                 ParseFunctionDecl();
        UniformBufferDeclPtr            ParseUniformBufferDecl();
        TextureDeclPtr                  ParseTextureDecl();
        SamplerDeclPtr                  ParseSamplerDecl();
        StructDeclPtr                   ParseStructDecl();
        DirectiveDeclPtr                ParseDirectiveDecl();

        FunctionCallPtr                 ParseAttribute();
        PackOffsetPtr                   ParsePackOffset(bool parseColon = true);
        ExprPtr                         ParseArrayDimension();
        ExprPtr                         ParseInitializer();
        VarSemanticPtr                  ParseVarSemantic();
        VarIdentPtr                     ParseVarIdent();
        VarTypePtr                      ParseVarType(bool parseVoidType = false);
        VarDeclPtr                      ParseVarDecl();

        StmntPtr                        ParseStmnt();
        CommentStmntPtr                 ParseCommentStmnt();
        NullStmntPtr                    ParseNullStmnt();
        DirectiveStmntPtr               ParseDirectiveStmnt();
        CodeBlockStmntPtr               ParseCodeBlockStmnt();
        ForLoopStmntPtr                 ParseForLoopStmnt(const std::vector<FunctionCallPtr>& attribs);
        WhileLoopStmntPtr               ParseWhileLoopStmnt(const std::vector<FunctionCallPtr>& attribs);
        DoWhileLoopStmntPtr             ParseDoWhileLoopStmnt(const std::vector<FunctionCallPtr>& attribs);
        IfStmntPtr                      ParseIfStmnt(const std::vector<FunctionCallPtr>& attribs);
        ElseStmntPtr                    ParseElseStmnt();
        SwitchStmntPtr                  ParseSwitchStmnt(const std::vector<FunctionCallPtr>& attribs);
        CtrlTransferStmntPtr            ParseCtrlTransferStmnt();
        VarDeclStmntPtr                 ParseVarDeclStmnt();
        ReturnStmntPtr                  ParseReturnStmnt();
        ExprStmntPtr                    ParseExprStmnt(const VarIdentPtr& varIdent = nullptr);
        StmntPtr                        ParseStructDeclOrVarDeclStmnt();
        StmntPtr                        ParseVarDeclOrAssignOrFunctionCallStmnt();

        ExprPtr                         ParseExpr(bool allowComma = false, const ExprPtr& initExpr = nullptr);
        ExprPtr                         ParsePrimaryExpr();
        LiteralExprPtr                  ParseLiteralExpr();
        ExprPtr                         ParseTypeNameOrFunctionCallExpr();
        UnaryExprPtr                    ParseUnaryExpr();
        ExprPtr                         ParseBracketOrCastExpr();
        ExprPtr                         ParseVarAccessOrFunctionCallExpr();
        VarAccessExprPtr                ParseVarAccessExpr(const VarIdentPtr& varIdent = nullptr);
        FunctionCallExprPtr             ParseFunctionCallExpr(const VarIdentPtr& varIdent = nullptr);
        InitializerExprPtr              ParseInitializerExpr();

        std::vector<VarDeclPtr>         ParseVarDeclList();
        std::vector<VarDeclStmntPtr>    ParseVarDeclStmntList();
        std::vector<VarDeclStmntPtr>    ParseParameterList();
        std::vector<StmntPtr>           ParseStmntList();
        std::vector<ExprPtr>            ParseExprList(const Tokens listTerminatorToken, bool allowLastComma = false);
        std::vector<ExprPtr>            ParseArrayDimensionList();
        std::vector<ExprPtr>            ParseArgumentList();
        std::vector<ExprPtr>            ParseInitializerList();
        std::vector<VarSemanticPtr>     ParseVarSemanticList();
        std::vector<FunctionCallPtr>    ParseAttributeList();
        std::vector<SwitchCasePtr>      ParseSwitchCaseList();
        std::vector<BufferDeclIdentPtr> ParseBufferDeclIdentList();

        std::string                     ParseRegister(bool parseColon = true);
        std::string                     ParseSemantic();

        /* === Members === */

        const Options&  options_;

        HLSLScanner     scanner_;

        Log*            log_ = nullptr;

};


} // /namespace HTLib


#endif



// ================================================================================