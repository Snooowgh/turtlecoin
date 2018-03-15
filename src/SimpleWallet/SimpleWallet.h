#include <cctype>

#include "INode.h"
#include "version.h"

#include <Common/ConsoleHandler.h>
#include <Common/SignalHandler.h>

#include <CryptoNoteCore/Account.h>
#include <CryptoNoteCore/Currency.h>

#include <Logging/FileLogger.h>
#include <Logging/LoggerManager.h>

#include <Mnemonics/electrum-words.h>

#include <NodeRpcProxy/NodeRpcProxy.h>

#include <SimpleWallet/PasswordContainer.h>
#include <SimpleWallet/Transfer.h>
#include <SimpleWallet/ParseArguments.h>

#include <System/Dispatcher.h>

#include <Wallet/WalletGreen.h>

#include <boost/thread/thread.hpp>

struct ThreadHandler {
    bool shouldDie = false;
    bool shouldPause = false;
    bool havePaused = false;
};

enum Action {Open, Generate, Import, SeedImport};

Action getAction();

void logIncorrectMnemonicWords(std::vector<std::string> words);

void promptSaveKeys(CryptoNote::WalletGreen &wallet);

void printPrivateKeys(CryptoNote::WalletGreen &wallet);

void balance(CryptoNote::INode &node, CryptoNote::WalletGreen &wallet);

void welcomeMsg();

void help();

void inputLoop(std::shared_ptr<WalletInfo> walletInfo, CryptoNote::INode &node,
               ThreadHandler &threadHandler);

void exportKeys(std::shared_ptr<WalletInfo> walletInfo);

void shutdown(CryptoNote::WalletGreen &wallet, CryptoNote::INode &node,
              ThreadHandler &threadHandler);

void run(CryptoNote::WalletGreen &wallet, CryptoNote::INode &node);

void blockchainHeight(CryptoNote::INode &node, CryptoNote::WalletGreen &wallet);

void listTransfers(bool incoming, bool outgoing, 
                   CryptoNote::WalletGreen &wallet);

void findNewTransactions(CryptoNote::INode &node, 
                         CryptoNote::WalletGreen &wallet);

void reset(CryptoNote::INode &node, std::shared_ptr<WalletInfo> walletInfo,
           ThreadHandler &threadHandler);

void printOutgoingTransfer(CryptoNote::WalletTransaction t);

void printIncomingTransfer(CryptoNote::WalletTransaction t);

void transactionWatcher(std::shared_ptr<WalletInfo> walletInfo,
                        ThreadHandler &threadHandler);

void confirmPassword(std::string);

bool isValidMnemonic(std::string &mnemonic_phrase, 
                     Crypto::SecretKey &private_spend_key);

std::string getNewWalletFileName();

std::string getExistingWalletFileName();

std::string getWalletPassword(bool verifyPwd);

std::shared_ptr<WalletInfo> importFromKeys(CryptoNote::WalletGreen &wallet, 
                           Crypto::SecretKey privateSpendKey,
                           Crypto::SecretKey privateViewKey);

std::shared_ptr<WalletInfo> openWallet(CryptoNote::WalletGreen &wallet);

std::shared_ptr<WalletInfo> importWallet(CryptoNote::WalletGreen &wallet);

std::shared_ptr<WalletInfo> mnemonicImportWallet(CryptoNote::WalletGreen 
                                                 &wallet);

std::shared_ptr<WalletInfo> generateWallet(CryptoNote::WalletGreen &wallet);

std::shared_ptr<WalletInfo> handleAction(CryptoNote::WalletGreen &wallet,
                                         Action action);

Crypto::SecretKey getPrivateKey(std::string outputMsg);

ColouredMsg getPrompt(std::shared_ptr<WalletInfo> walletInfo);
