#include "AffectsStarClauseEvaluator.h"

bool AffectsStarClauseEvaluator::HandleBothWildcard() {
  // Example query: Affects*(_, _)
  return pkb_->IsThereAnyAffectsStarRelationship();
}

bool AffectsStarClauseEvaluator::HandleFirstWildcardSecondValue() {
  // Example query: Affects*(_, 6)
  return !pkb_->GetAssignsAffectingStar(second_arg_).empty();
}

bool AffectsStarClauseEvaluator::HandleFirstValueSecondWildcard() {
  // Example query: Affects*(6, _)
  return !pkb_->GetAssignsAffectedStarBy(first_arg_).empty();
}

bool AffectsStarClauseEvaluator::HandleBothValue() {
  // Example query: Affects*(6, 5)
  return pkb_->HasAffectsStarRelationship(first_arg_, second_arg_);
}

ResultTable AffectsStarClauseEvaluator::HandleBothSynonym() {
  if (!is_first_arg_a_valid_syn_ || !is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects(a, a1)
  PkbCommunicationTypes::PairConstraintSet pair_constraint = pkb_->GetAffectsStarPairs();

  if (is_same_syn_or_value_pairs_) {
    pair_constraint = ClauseEvaluator::FilterForSameSynonym(pair_constraint);
  }
  return ConvertPairSetToResultTableFormat(pair_constraint);
}

ResultTable AffectsStarClauseEvaluator::HandleFirstSynonymSecondWildcard() {
  if (!is_first_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects*(a, _)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAffectStar());
}

ResultTable AffectsStarClauseEvaluator::HandleFirstSynonymSecondValue() {
  if (!is_first_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects*(a,6)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectingStar(second_arg_));
}

ResultTable AffectsStarClauseEvaluator::HandleFirstWildcardSecondSynonym() {
  if (!is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects*(_,a)
  return ConvertSetToResultTableFormat(pkb_->GetAllAssignsThatAreAffectedStar());
}

ResultTable AffectsStarClauseEvaluator::HandleFirstValueSecondSynonym() {
  if (!is_second_arg_a_valid_syn_) {
    return {};
  }
  // Example query: Affects*(6, a)
  return ConvertSetToResultTableFormat(pkb_->GetAssignsAffectedStarBy(first_arg_));
}
