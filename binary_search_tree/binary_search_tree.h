#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <queue>

namespace BINARY_SEARCH_TREE {

template <typename Key, typename Value>
class BinarySearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node(const Key &k, const Value &v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* m_root;
    int m_count;

public:
    BinarySearchTree() : m_root(nullptr), m_count(0) {}

    // 后序遍历释放空间
    virtual ~BinarySearchTree()
    {
        destroy(m_root);
    }

    bool empty() const
    {
        return m_count == 0;
    }

    int size() const
    {
        return m_count;
    }

    /**
     * @brief 添加二分搜索树的节点，重复键时更新值（没有重复键的节点）
     */
    void insert(const Key &key, const Value &value)
    {
        m_root = insert(m_root, key, value);
    }

    bool contains(const Key &key) const
    {
        return contains(m_root, key);
    }

    /**
     * @brief 在二分搜索树中查找键是key的节点
     */
    Value *search(const Key &key) const
    {
        return search(m_root, key);
    }

    void preOrder(){
        preOrder(m_root);
        std::cout << std::endl; // 方便测试
    }

    void midOrder(){
        midOrder(m_root);
        std::cout << std::endl;
    }

    void postOrder(){
        postOrder(m_root);
        std::cout << std::endl;
    }

    /**
     * @brief 层序遍历，广度优先遍历
     */
    void levelOrder()
    {
        if (m_root == nullptr) {
            return;
        }

        std::queue<Node*> queue{};
        queue.push(m_root);

        Node *curNode = nullptr;
        while (!queue.empty()) {
            curNode = queue.front();
            queue.pop();
            std::cout << curNode->key<< " ";

            if (curNode->left != nullptr) {
                queue.emplace(curNode->left);
            }

            if (curNode->right != nullptr) {
                queue.emplace(curNode->right);
            }
        }

        std::cout << std::endl;
    }

private:
    /**
     * @brief 向以node为根的二叉搜索树中插入节点(key, value)
     * @return 返回插入新节点后的二叉搜索树的根 
     */
    Node *insert(Node *node, const Key &key, const Value &value)
    {
        if (node == nullptr) {
            ++m_count;
            return new Node(key, value);
        }

        if (key == node->key) {
            node->value = value;
        } else if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else {
            node->right = insert(node->right, key, value);
        }

        return node;
    }

    bool contains(Node *node, const Key &key) const
    {
        if (node == nullptr) {
            return false;
        }

        if (key == node->key) {
            return true;
        }

        if (key < node->key) {
            return contains(node->left, key);
        }

        return contains(node->right, key);
    }

    Value *search(Node *node, const Key &key) const
    {
        if (node == nullptr) {
            return nullptr;
        }

        if (key == node->key) {
            return &(node->value);
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    void preOrder(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        std::cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void midOrder(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        midOrder(node->left);
        std::cout << node->key << " ";
        midOrder(node->right);
    }

    void postOrder(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->key << " ";
    }

    void destroy(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        delete node;
        --m_count;
    }

    void levelOrder(Node *node)
    {
        if (node == nullptr) {
            return;
        }

        std::queue<Node*> queue{};
        queue.push(node);

        Node *curNode = nullptr;
        while (!queue.empty()) {
            curNode = queue.front();
            queue.pop();
            std::cout << curNode->key<< " ";

            if (curNode->left != nullptr) {
                queue.emplace(curNode->left);
            }

            if (curNode->right != nullptr) {
                queue.emplace(curNode->right);
            }
        }
    }
};

}
#endif