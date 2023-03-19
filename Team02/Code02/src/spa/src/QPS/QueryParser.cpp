#include "QueryParser.h"

std::shared_ptr<Query> QueryParser::ParseQuery(std::string query) {
  std::shared_ptr<QpsTokenizer> tk = std::make_shared<QpsTokenizer>();
  std::string query_trimmed = string_util::RemoveExtraWhitespacesInString(query);

  QueryLinesPair declaration_select_pair;
  declaration_select_pair = tk->SplitQuery(query_trimmed);

  std::vector<std::string> declarations = declaration_select_pair.first;
  Map declaration_map = tk->ExtractAbstractSyntaxFromDeclarations(declarations);

  // Already checked if the statement starts with Select
  std::string trimmed_select_statement = declaration_select_pair.second;
  std::string remaining_clause = string_util::Trim(trimmed_select_statement
      .substr(pql_constants::kSelectKeyword.length()));

  SelectedSynonymTuple synonym_tuple = tk->ParseSynonym(remaining_clause, declaration_map);

  std::string clause_substring = tk->GetSubclauseString(remaining_clause, synonym_tuple);
  ClauseSyntaxPtrList syntax_pair_list;
  if (!clause_substring.empty()) {
    syntax_pair_list = tk->ParseSubClauses(clause_substring);
  }

  if (tk->semantic_validator_->HasSemanticError()) {
    throw SemanticErrorException();
  }

  // consolidate parsing result
  std::shared_ptr<Query> query_ptr = std::make_shared<Query>(synonym_tuple, declaration_map, syntax_pair_list);
  return query_ptr;
}
