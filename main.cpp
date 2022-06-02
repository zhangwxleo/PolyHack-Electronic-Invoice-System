#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include <unordered_map> //data structure of DFS

#include "SHA1.hpp"
#include "SHA1.cpp"
#include "Block.h"
#include "Chain.h"

using namespace std;


unordered_map <string,int> DFS;

// This function provides the user with some functions to choose.
//      Only a single character is allowed.
void menu();
void tax_payer_menu();
void add_blocks(Chain& transaction_info);
// 用户申请查看交易信息
void supervision(Chain transaction_info);
// 检查是否存在该信息
bool check_transaction(Chain transaction_info, string info);
// 用户申请报销
void reimburse(Chain& transaction_info, Chain& reim_record);


int main()
{
    Chain transaction_info;
    Chain reim_record;
    DFS.clear();

    menu();
    int choice;
    cin>>choice;
    while (cin.fail() || cin.peek() != '\n')
    {
        cin.clear();
        // clear the input stream
        cin.ignore(std::numeric_limits< streamsize >::max(),'\n');
        cout<<"Please enter a valid choice. (1/2/0): ";
        cin>>choice;
    }
    while (choice != 0)
    {
        switch (choice)
        {
            //  Third party platform/ tax authority mode
            case 1:
            {
                add_blocks(transaction_info);
                break;
            }

            // tax payer mode
            case 2:
            {
                int choice2;
                tax_payer_menu();
                cin >> choice2;
                while (cin.fail() || cin.peek() != '\n') {
                    cin.clear();
                    // clear the input stream
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid choice. (1/2): ";
                    cin >> choice2;
                }
                if (choice2 == 1)
                {
                    supervision(transaction_info);
                }
                else if (choice2 == 2)
                {
                    reimburse(transaction_info, reim_record);
                }
                break;
            }
        }
        menu();
        cin>>choice;
        while (cin.fail() || cin.peek() != '\n')
        {
            cin.clear();
            // clear the input stream
            cin.ignore(std::numeric_limits< streamsize >::max(),'\n');
            cout<<"Please enter a valid choice. (1/2/0): ";
            cin>>choice;
        }
    }

    cout<<"Thanks for using the electronic invoice system!"<<endl;

    return 0;
}


void menu()
{
    cout << "========================================================================================================"<<endl;
    cout << "This is the demonstration of electronic invoice system based on double-blockchain. Please choose a mode: \n";
    cout << "(1) Enter '1' to explore administrator mode.\n"
            "(2) Enter '2' to explore tax payer mode. \n"
            "(3) Enter '0' to quit\n";
    cout << "Please enter your choice: ";
}

void tax_payer_menu()
{
    cout << "-------------------------------------------"<<endl;
    cout<<"As a tax payer, you are able to:\n";
    cout<<"(1) Enter 1 to conduct supervision\n";
    cout<<"(2) Enter 2 to apply for reimbursement.\n"
          "(3) Any other key to quit the tax payer mode.\n";
    cout<<"Please enter your choice: ";
}

void add_blocks(Chain& transaction_info)
{
    cout<<"This is the administrator mode. You are able to collect users' information and add blocks."<<endl;
    cin.get();
    vector<Block>::iterator iter;
    iter = transaction_info.blockchain.end();
    int index = iter[-1].Index + 1;
    string prehash = iter[-1].Hash;
    Block t(index, prehash);
    t.input();
    // Get the data and time stamp of the new block.
    t.getTime(); //?
    // Add the new block to the tail of the blockchain.
    transaction_info.blockchain.push_back(t);
    //add to DFS
    auto it = DFS.find(t.data);    // 改成t.data
    if (DFS.empty() || it == DFS.end()) {
        DFS[t.data] = 100;
    }
    cout<<"The block has been added to the blockchain. Feel free to explore other functions."<<endl;
}



// 用户申请查看交易信息
void supervision(Chain transaction_info)
{
    if (transaction_info.ifValid(transaction_info))
    {
        if (transaction_info.blockchain.size() == 1)
            cout << "There's no transaction information yet." << endl;
        else
        {
            cout << "The transaction information chain is valid, you are able to check the data." << endl;

            cin.get();
            string user_name;
            cout<<"Please enter the user (buyer's) name: ";
            getline(cin,user_name);

            bool find = false;
            // Display each block's data first.
            for (int i = 1; i < transaction_info.blockchain.size(); i++)
            {
                if (transaction_info.blockchain[i].name == user_name)
                {
                    find = true;
                    cout << "The No." << transaction_info.blockchain[i].Index << " block's transaction information is: "
                         << transaction_info.blockchain[i].data << endl;
                }
            }
            if (find == false)
            {
                cout<<"The transaction information isn't found in our record."<<endl;
            }
            cout << "Done. You could explore other functions." << endl;
        }
    }
    else
        cout << "This chain has been changed maliciously. Unable to check the data." << endl;
}

// 检查是否存在该信息
bool check_transaction(Chain transaction_info, string info)
{
    for (int i = 1; i<transaction_info.blockchain.size(); i++)
    {
        if (info == transaction_info.blockchain[i].data)
            return true;
    }
    return false;
}

// 用户申请报销
void reimburse(Chain& transaction_info, Chain& reim_record)
{
    string info1;
    string buyer;
    cin.get();
    cout<<"Please input the buyer: ";
    getline(cin,buyer);
    string solder;
    cout<<"Please input the seller: ";
    getline(cin,solder);
    string transaction_amount;
    cout<<"Please enter the transaction amount: ";
    getline(cin,transaction_amount);
    info1 = "buyer: "+buyer+"; seller: "+solder+"; amount: "+transaction_amount;
    if (DFS.find(info1) != DFS.end() && DFS[info1] <= 80) {
        cout << "Because your credit rating is substandard, you cannot use electronic invoice system to apply for reimbursement " << endl
             << "please contact staff or use traditional methods to apply for reimbursement." << endl;
        return;
    }

    if (check_transaction(transaction_info, info1))
    {
        bool if_reim = false;
        for (int i = 1; i<reim_record.blockchain.size(); i++)
        {
            if (info1 == reim_record.blockchain[i].data)
            {
                if_reim = true;
            }
        }
        if (if_reim)
        {
            cout << "The invoice has been reimbursed. You are suspected of repeatedly reimbursement." << endl;
            //record the behavior of reimbursement
            DFS[info1] -= 10;

        }
        else
        {
            cout<<"The invoice is ready to be reimbursed...\nThe reimbursement is completed"<<endl;
            vector<Block>::iterator iter;
            iter = reim_record.blockchain.end();
            int index = iter[-1].Index + 1;
            string prehash = iter[-1].Hash;
            Block t(index, prehash);
            // Get the data and time stamp of the new block.
            t.data = info1;
            t.getTime();
            // Add the new block to the tail of the blockchain.
            reim_record.blockchain.push_back(t);
        }
    }
    else
    {
        cout<<"The invoice doesn't exist. You are suspected of invoice fraud."<<endl;

        if (!DFS.empty() && DFS.find(buyer) != DFS.end()) {
            DFS[info1] -= 10;
        } else {
            DFS[info1] = 90;
        }
    }
}
