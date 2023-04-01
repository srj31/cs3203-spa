#include "ParentClauseEvaluator.h"

bool ParentClauseEvaluator::CheckIfReturnEmpty() {
  bool is_first_arg_not_a_container_syn = QueryUtil::IsSynonym(first_arg_)
      && !QueryUtil::IsIfSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsWhileSynonym(declaration_map_, first_arg_)
      && !QueryUtil::IsStatementSynonym(declaration_map_, first_arg_);
  bool is_same_syn_or_value_pairs = (first_arg_ == second_arg_) && !QueryUtil::IsWildcard(first_arg_);
  return is_first_arg_not_a_container_syn || is_same_syn_or_value_pairs;
}

bool ParentClauseEvaluator::HandleBothWildcard() {
  // Example query: Parent(_,_)
  return pkb_->IsAnyParentRelationshipPresent();
}

bool ParentClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Parent(_,"5")
  return !pkb_->GetStatementThatIsParentOf(second_arg_, StatementType::STATEMENT).empty();
}

bool ParentClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Parent("5", _)
  return !pkb_->GetStatementsThatAreChildrenOf(first_arg_, StatementType::STATEMENT).empty();
}

bool ParentClauseEvaluator::HandleBothValue() {
  // Example query: Parent(5, 6)
  return pkb_->HasParentChildRelationship(first_arg_, second_arg_);
}

ResultTable ParentClauseEvaluator::HandleBothSynonym() {
  // Example query: Parent(a,p)
  return ConvertPairSetToResultTableFormat(pkb_->GetParentChildPairs(arg_1_type_, arg_2_type_));
}

ResultTable ParentClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  // Example query: Parent(s, _)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreParents(arg_1_type_));
}

ResultTable ParentClauseEvaluator::HandleFirstSynonymSecondValue() {
  // Example query: Parent(a,"5")
  return ConvertSetToResultTableFormat(pkb_->GetStatementThatIsParentOf(second_arg_, arg_1_type_));
}

ResultTable ParentClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  // Example query: Parent(_, s)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreChildren(arg_2_type_));
}

ResultTable ParentClauseEvaluator::HandleFirstValueSecondSynonym() {
  // Example query: Parent("5", a)
  return ConvertSetToResultTableFormat(pkb_->GetStatementsThatAreChildrenOf(first_arg_, arg_2_type_));
}
