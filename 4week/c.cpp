#include <iostream>
#define MAX_SIZE 100

using namespace std;

class TreeNode {
public:
    int data;
};

class Tree {
public:
    TreeNode* nodes[MAX_SIZE];
    int size;

    Tree() {
        size = 0;
    }

    void addNode(int data) {
        TreeNode* node = new TreeNode();
        node->data = data;
        nodes[size++] = node;
    }

    void addEdge(int parentIndex, int childIndex) {
        if (parentIndex >= size || childIndex >= size) {
            cout << "인덱스 오류" << endl;
            return;
        }
        nodes[parentIndex]->children.push_back(nodes[childIndex]);
    }

    void traverse(TreeNode* node) {
        if (!node) return;
        cout << node->data << " ";
        for (TreeNode* child : node->children) {
            traverse(child);
        }
    }
};

int main() {
    Tree tree;
    tree.addNode(1); // 0번 노드
    tree.addNode(2); // 1번 노드
    tree.addNode(3); // 2번 노드
    tree.addNode(4); // 3번 노드
    tree.addNode(5); // 4번 노드

    tree.addEdge(0, 1); // 0번 노드의 자식으로 1번 노드 추가
    tree.addEdge(0, 2); // 0번 노드의 자식으로 2번 노드 추가
    tree.addEdge(1, 3); // 1번 노드의 자식으로 3번 노드 추가
    tree.addEdge(2, 4); // 2번 노드의 자식으로 4번 노드 추가

    tree.traverse(tree.nodes[0]); // 1 2 4 3 5 출력

    return 0;
}
