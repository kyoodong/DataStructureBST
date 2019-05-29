#include <iostream>

using std::cout;
using std::endl;

template <typename K, typename V>
class BinarySearchTree {
public:
    BinarySearchTree(): head(NULL) {}

    void Insert(const std::pair<K, V>& p);
    void Inorder() const;
    void Delete(const K key);
    std::pair<K, V> Get(const K key) const;
private:
    class Node {
    public:
        Node(const std::pair<K, V>& p):
            keyVal(p), leftChild(NULL), rightChild(NULL) {
        }

        int operator*() const {
            return keyVal.second;
        }

        std::pair<K, V> keyVal;
        Node* leftChild;
        Node* rightChild;
    private:
    };

    Node* head;
    void _Inorder(const Node& node) const;
    void Visit(const Node& node) const;
};

template <typename K, typename V>
void BinarySearchTree<K,V>::Insert(const std::pair<K, V> &p) {
    if (head == NULL) {
        head = new Node(p);
        return;
    }

    Node* node = head;
    while (node != NULL) {
        if (p.first < node->keyVal.first) {
            if (node->leftChild == NULL) {
                node->leftChild = new Node(p);
                return;
            }
            node = node->leftChild;
        } else {
            if (node->rightChild == NULL) {
                node->rightChild = new Node(p);
                return;
            }
            node = node->rightChild;
        }
    }
}

template <typename K, typename V>
std::pair<K, V> BinarySearchTree<K,V>::Get(const K key) const {
    Node* node = head;
    while (node != NULL) {
        if (node->keyVal.first == key)
            return node->keyVal;

        else if (key < node->keyVal.first) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
    throw "없습니다.";
}

template <typename K, typename V>
void BinarySearchTree<K,V>::Inorder() const {
    if (head == NULL)
        return;

    _Inorder(*head);
}

template <typename K, typename V>
void BinarySearchTree<K,V>::Delete(const K key) {
    Node* prev = head;
    Node* node = head;
    while (node != NULL) {
        if (node->keyVal.first == key)
            break;
        prev = node;

        if (key < node->keyVal.first) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }

    if (node == NULL)
        throw "일치하는 key값을 가진 요소가 없습니다.";

    Node* subNode = NULL;
    Node* prevSubNode = node;
    if (node->leftChild != NULL) {
        subNode = node->leftChild;
        while (subNode->rightChild != NULL) {
            prevSubNode = subNode;
            subNode = subNode->rightChild;
        }

        if (prevSubNode == node)
            prevSubNode->leftChild = NULL;
        else
            prevSubNode->rightChild = NULL;
    } else if (node->rightChild != NULL) {
        subNode = node->rightChild;
        while (subNode->leftChild != NULL) {
            prevSubNode = subNode;
            subNode = subNode->leftChild;
        }

        if (prevSubNode == node)
            prevSubNode->rightChild = NULL;
        else
            prevSubNode->leftChild = NULL;
    } else {
        if (prev->leftChild->keyVal.first == key) {
            delete prev->leftChild;
            prev->leftChild = NULL;
        }
        else {
            delete prev->rightChild;
            prev->rightChild = NULL;
        }
        return;
    }

    if (prev->keyVal.first == key)
        head->keyVal = subNode->keyVal;
    else if (prev->leftChild->keyVal.first == key)
        prev->leftChild->keyVal= subNode->keyVal;
    else
        prev->rightChild->keyVal = subNode->keyVal;

    // 밑에 자식 주소 있을 수도 있는데 이거 처리해줘야되나...??
    delete subNode;
}

template <typename K, typename V>
void BinarySearchTree<K,V>::_Inorder(const BinarySearchTree::Node& node) const {
    if (node.leftChild != NULL)
        _Inorder(*node.leftChild);

    Visit(node);

    if (node.rightChild != NULL)
        _Inorder(*node.rightChild);
}

template <typename K, typename V>
void BinarySearchTree<K,V>::Visit(const BinarySearchTree::Node& node) const {
    cout << *node << endl;
}

int main() {
    BinarySearchTree<int, int> bst;
    bst.Insert(std::pair<int, int>(8, 88));
    bst.Insert(std::pair<int, int>(4, 44));
    bst.Insert(std::pair<int, int>(9, 99));
    bst.Insert(std::pair<int, int>(2, 22));
    bst.Insert(std::pair<int, int>(1, 11));
    bst.Insert(std::pair<int, int>(6, 66));
    bst.Insert(std::pair<int, int>(3, 33));
    bst.Insert(std::pair<int, int>(5, 55));
    bst.Insert(std::pair<int, int>(7, 77));

    cout << "중위순회하여 second 값 모두 출력" << endl;
    bst.Inorder();

    cout << "노드 4 삭제" << endl;
    bst.Delete(4);

    cout << "중위순회하여 second 값 모두 출력" << endl;
    bst.Inorder();

    cout << "노드 5 삭제" << endl;
    bst.Delete(5);

    cout << "중위순회하여 second 값 모두 출력" << endl;
    bst.Inorder();

    cout << "노드 2 삭제" << endl;
    bst.Delete(2);

    cout << "중위순회하여 second 값 모두 출력" << endl;
    bst.Inorder();

    try {
        cout << "노드 2가 있는지 확인" << endl;
        std::pair<int, int> p = bst.Get(2);
        cout << p.second << endl;
    } catch (const char* err) {
        cout << err << endl;
    }

    try {
        cout << "노드 9가 있는지 확인" << endl;
        std::pair<int, int> p = bst.Get(9);
        cout << p.second << endl;
    } catch (const char* err) {
        cout << err << endl;
    }
    return 0;
}