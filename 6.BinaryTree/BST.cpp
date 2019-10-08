//代码参考：https://blog.csdn.net/lining0420/article/details/76167901

#include <iostream>
#include <stack>
using namespace std;

typedef struct STreeNode *pSTreeNode;
typedef int TreeKeyType;

struct STreeNode
{
    TreeKeyType key;
    pSTreeNode pLeftChild;
    pSTreeNode pRightChild;

    STreeNode(TreeKeyType Value)
    {
        key = Value;
        pLeftChild = NULL;
        pRightChild = NULL;
    }
};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();

    void Insert(TreeKeyType Value);
    void Insert(pSTreeNode pNode, TreeKeyType Value);

    pSTreeNode Search(TreeKeyType Value);
    pSTreeNode Search(pSTreeNode pNode, TreeKeyType Value);

    void Delete(TreeKeyType Value);

    void Preorder();  // 前序遍历，非递归方法（借用堆栈）
    void Inorder();   // 中序遍历，非递归方法（借用堆栈）
    void Postorder(); // 后序遍历，非递归方法（借用堆栈）

    void PreorderRecursively(pSTreeNode pNode);  // 前序遍历，递归调用
    void InorderRecursively(pSTreeNode pNode);   // 中序遍历，递归调用
    void PostorderRecursively(pSTreeNode pNode); // 后序遍历，递归调用

    pSTreeNode GetMaxKey(); // 获取二叉查找树中元素值最大的节点
    pSTreeNode GetMinKey(); // 获取二叉查找树中元素值最小的节点

    void FreeMemory(pSTreeNode pNode);

public:
    pSTreeNode pRoot;
};

CBinTree::CBinTree()
{
    pRoot = NULL;
}

CBinTree::~CBinTree()
{
    if (pRoot == NULL)
    {
        return;
    }

    FreeMemory(pRoot);
}

void CBinTree::FreeMemory(pSTreeNode pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    if (pNode->pLeftChild != NULL)
    {
        FreeMemory(pNode->pLeftChild);
    }

    if (pNode->pRightChild != NULL)
    {
        FreeMemory(pNode->pRightChild);
    }

    delete pNode;
    pNode = NULL;
}

void CBinTree::Insert(TreeKeyType Value)
{
    if (pRoot == NULL)
    {
        pRoot = new STreeNode(Value);
    }
    else
    {
        Insert(pRoot, Value);
    }
}

void CBinTree::Insert(pSTreeNode pNode, TreeKeyType Value)
{
    if (pNode->key > Value)
    {
        if (pNode->pLeftChild == NULL)
        {
            pNode->pLeftChild = new STreeNode(Value);
        }
        else
        {
            Insert(pNode->pLeftChild, Value);
        }
    }
    else
    {
        if (pNode->pRightChild == NULL)
        {
            pNode->pRightChild = new STreeNode(Value);
        }
        else
        {
            Insert(pNode->pRightChild, Value);
        }
    }
}

pSTreeNode CBinTree::Search(TreeKeyType Value)
{
    return Search(pRoot, Value);
}

pSTreeNode CBinTree::Search(pSTreeNode pNode, TreeKeyType Value)
{
    if (pNode == NULL)
    {
        return NULL;
    }

    if (pNode->key == Value)
    {
        return pNode;
    }
    else
    {
        if (pNode->key > Value)
        {
            return Search(pNode->pLeftChild, Value);
        }
        else
        {
            return Search(pNode->pRightChild, Value);
        }
    }
}

void CBinTree::Delete(TreeKeyType Value)
{
    pSTreeNode pParentNode = pRoot;
    pSTreeNode pFindNode = pRoot;
    // 找到Value元素对应的节点
    while (pFindNode != NULL)
    {
        if (pFindNode->key == Value)
        {
            break;
        }
        pParentNode = pFindNode;
        if (pFindNode->key > Value)
        {
            pFindNode = pFindNode->pLeftChild;
        }
        else
        {
            pFindNode = pFindNode->pRightChild;
        }
    }

    if (pFindNode == NULL)
    {
        return;
    }

    // 处理Value元素的父节点和Value元素的节点
    if (pFindNode->pLeftChild == NULL || pFindNode == NULL)
    {
        // 一个子节点为空或者两个字节点都为空
        pSTreeNode pTemp = NULL;
        if (pFindNode->pLeftChild != NULL)
        {
            pTemp = pFindNode->pLeftChild;
        }
        else if (pFindNode->pRightChild != NULL)
        {
            pTemp = pFindNode->pRightChild;
        }

        if (pParentNode->pLeftChild == pFindNode)
        {
            pParentNode->pLeftChild = pTemp;
        }
        else
        {
            pParentNode->pRightChild = pTemp;
        }

        delete pFindNode;
        pFindNode = NULL;
    }
    else
    {
        // 找到前驱节点
        pSTreeNode pTemp = pFindNode->pLeftChild;
        pSTreeNode pTempParent = pFindNode;

        while (pTemp->pRightChild != NULL)
        {
            pTempParent = pTemp;
            pTemp = pTemp->pRightChild;
        }

        pFindNode->key = pTemp->key;
        pTempParent->pRightChild = NULL;
        delete pTemp;
        pTemp = NULL;
    }
}

void CBinTree::Preorder()
{
    if (pRoot == NULL)
    {
        cout << "This is a empty binary tree." << endl;
        return;
    }
    stack<pSTreeNode> StackTree;
    pSTreeNode pNode = pRoot;
    while (pNode != NULL || !StackTree.empty())
    {
        while (pNode != NULL)
        {
            cout << " " << pNode->key << " ";
            StackTree.push(pNode);
            pNode = pNode->pLeftChild;
        }

        pNode = StackTree.top();
        StackTree.pop();
        pNode = pNode->pRightChild;
    }
}

void CBinTree::Inorder( )
{
    if ( pRoot == NULL )
    {
        cout << "This is a empty binary tree." << endl;
        return;
    }

    stack<pSTreeNode> StackTree;
    pSTreeNode pNode = pRoot;
    while ( pNode != NULL || !StackTree.empty() )
    {
        while ( pNode != NULL )
        {
            StackTree.push( pNode );
            pNode = pNode->pLeftChild;
        }

        pNode = StackTree.top();
        StackTree.pop();
        cout << " " << pNode->key << " ";
        pNode = pNode->pRightChild;
    }
}

//  借助变量visited表示是否访问过该根节点。访问过的话，这输出。
void CBinTree::Postorder()
{
    if (pRoot == NULL)
    {
        cout << "This is a empty binary tree." << endl;
        return;
    }

    stack<pair<pSTreeNode, bool>> StackTree;
    StackTree.push(make_pair(pRoot, false));

    while (!StackTree.empty())
    {
        pSTreeNode pNode = StackTree.top().first;
        bool bVisited = StackTree.top().second;

        if (pNode == NULL)
        {
            StackTree.pop();
            continue;
        }

        if (bVisited)
        {
            cout << " " << pNode->key << " ";
            StackTree.pop();
        }
        else
        {
            StackTree.top().second = true;
            StackTree.push(make_pair(pNode->pRightChild, false));
            StackTree.push(make_pair(pNode->pLeftChild, false));
        }
    }
}

void CBinTree::PreorderRecursively(pSTreeNode pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    cout << " " << pNode->key << " ";
    PreorderRecursively(pNode->pLeftChild);
    PreorderRecursively(pNode->pRightChild);
}

void CBinTree::InorderRecursively(pSTreeNode pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    InorderRecursively(pNode->pLeftChild);
    cout << " " << pNode->key << " ";
    InorderRecursively(pNode->pRightChild);
}

void CBinTree::PostorderRecursively(pSTreeNode pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    PostorderRecursively(pNode->pLeftChild);
    PostorderRecursively(pNode->pRightChild);
    cout << " " << pNode->key << " ";
}

pSTreeNode CBinTree::GetMaxKey()
{
    pSTreeNode pNode = pRoot;
    if (pNode == NULL)
    {
        return NULL;
    }
    while (pNode->pRightChild != NULL)
    {
        pNode = pNode->pRightChild;
    }
    return pNode;
}

pSTreeNode CBinTree::GetMinKey()
{
    pSTreeNode pNode = pRoot;
    if (pNode == NULL)
    {
        return NULL;
    }
    while (pNode->pLeftChild != NULL)
    {
        pNode = pNode->pLeftChild;
    }
    return pNode;
}

int main()
{
    CBinTree *pBinTree = new CBinTree();
    if (pBinTree == NULL)
    {
        return 0;
    }

    pBinTree->Insert(15);
    pBinTree->Insert(3);
    pBinTree->Insert(20);
    pBinTree->Insert(8);
    pBinTree->Insert(10);
    pBinTree->Insert(18);
    pBinTree->Insert(6);
    pBinTree->Insert(1);
    pBinTree->Insert(26);

    pSTreeNode pRoot = pBinTree->pRoot;

    cout << "Preorder: ";
    pBinTree->Preorder();
    cout << endl;

    cout << "PreorderRecursively: ";
    pBinTree->PreorderRecursively(pRoot);
    cout << endl;

    cout << "Inorder: ";
    pBinTree->Inorder();
    cout << endl;

    cout << "InorderRecursively: ";
    pBinTree->InorderRecursively(pRoot);
    cout << endl;

    cout << "Postorder: ";
    pBinTree->Postorder();
    cout << endl;

    cout << "PostorderRecursively: ";
    pBinTree->PostorderRecursively(pRoot);
    cout << endl;

    pSTreeNode pMaxNode = pBinTree->GetMaxKey();
    pSTreeNode pMinNode = pBinTree->GetMinKey();
    if (pMaxNode != NULL)
    {
        cout << "MaxKey: " << pMaxNode->key << endl;
    }

    if (pMinNode != NULL)
    {
        cout << "MinKey: " << pMinNode->key << endl;
    }

    TreeKeyType DeleteKey = 15;
    pSTreeNode pSearchNode = pBinTree->Search(DeleteKey);
    if (pSearchNode != NULL)
    {
        cout << "search elem is: " << DeleteKey << ", searched elem is: " << pSearchNode->key << endl;
    }
    else
    {
        cout << "no elem: " << DeleteKey << endl;
    }
    pBinTree->Delete(DeleteKey);
    cout << "delete elem " << DeleteKey << " preorder: ";
    pBinTree->PreorderRecursively(pRoot);
    cout << endl;

    DeleteKey = 1;
    pBinTree->Delete(DeleteKey);
    cout << "delete elem " << DeleteKey << " PreorderRecursively: ";
    pBinTree->PreorderRecursively(pRoot);
    cout << endl;

    DeleteKey = 26;
    pBinTree->Delete(DeleteKey);
    cout << "delete elem " << DeleteKey << " PreorderRecursively: ";
    pBinTree->PreorderRecursively(pRoot);
    cout << endl;

    // ！！！删除8后运行会问题，待解决
    // DeleteKey = 8;
    // pBinTree->Delete(DeleteKey);
    // cout << "delete elem " << DeleteKey << " PreorderRecursively: ";
    // pBinTree->PreorderRecursively(pRoot);
    // cout << endl;

    delete pBinTree;
    pBinTree = NULL;
    system("pause");
    return 0;
}
