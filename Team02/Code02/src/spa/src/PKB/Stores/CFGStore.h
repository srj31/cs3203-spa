#pragma once

#include <memory>
#include "core/cfg_model/Cfg.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class CFGStore
 * Class representing the CFG Store in PKB.
 *
 * The CFGStore class is responsible for maintaining information about the
 * control flow graph of the source program.
 *
 */
class CFGStore {
 public:
  /**
   * Constructor for the CFGStore class.
   */
  CFGStore();

  /**
   * Destructor for the CFGStore class.
   */
  ~CFGStore();

  /**
   * Adds the control flow graph to the store.
   *
   * @param cfg - The CFG to be added.
   */
  void addCfg(std::shared_ptr<Cfg> cfg);

  /**
   * Retrieves the CFG given a procedure.
   *
   * @param procedure - The procedure whose CFG is to be retrieved.
   * @return The root node of the CFG for the given procedure.
   */
  std::shared_ptr<CfgNode> getCfgNodeFromProcedure(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves the CFG node given a statement number.
   *
   * @param statement_number - The statement number representing the statement whose CFG node is to be retrieved.
   * @return The CFG node for the given statement number.
   */
  std::shared_ptr<CfgNode> getCfgNodeFromStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number);

  /**
   * Returns the CFG stored in this CFGStore.
   *
   * @return The CFG stored in this CFGStore.
   */
  std::shared_ptr<Cfg> getCfg() const;

 private:
  std::shared_ptr<Cfg> cfg_;
};

