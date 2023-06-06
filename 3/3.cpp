#include <iostream>
#include <string>
#include <locale>


using namespace std;

struct TreeNode
{
    string filename;
    int date;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* deleteOldFiles(TreeNode* root, int dateToDelete)
{
    if (root == NULL)
        return root;

    root->left = deleteOldFiles(root->left, dateToDelete);

    root->right = deleteOldFiles(root->right, dateToDelete);

    if (root->date <= dateToDelete)
    {
        TreeNode* temp = root;
        root = root->right;
        delete temp;
    }

    return root;
}

TreeNode* newNode(string filename, int date)
{
    TreeNode* node = new TreeNode;
    node->filename = filename;
    node->date = date;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insertNode(TreeNode* root, string filename, int date)
{
    if (root == NULL)
        return newNode(filename, date);

    if (filename < root->filename)
        root->left = insertNode(root->left, filename, date);
    else
        root->right = insertNode(root->right, filename, date);

    return root;
}

void displayTree(TreeNode* root)
{
    if (root != NULL)
    {
        displayTree(root->left);
        cout << root->filename << " - " << root->date << endl;
        displayTree(root->right);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    TreeNode* root = NULL;
    root = insertNode(root, "file1.txt", 20211201);
    insertNode(root, "file2.txt", 20220101);
    insertNode(root, "file3.txt", 20210630);
    insertNode(root, "file4.txt", 20221231);

    cout << "Первоначальное дерево:" << endl;
    displayTree(root);

    int dateToDelete;
    cout << "\nВведите дату в формате YYYYMMDD чтобы удалить файлы созданные до введенной даты: ";
    cin >> dateToDelete;
    root = deleteOldFiles(root, dateToDelete); 

    cout << "\nОбновленное дерево:" << endl;
    displayTree(root);

    return 0;
}