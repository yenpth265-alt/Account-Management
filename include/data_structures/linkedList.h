#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
//Cấu trúc Node
template <class T>
struct Node {
    T data;
    Node* next;
    //hàm khởi tạo node
    Node(T newData){
        this->data = newData;
        this->next = nullptr;
    }
};
//Cấu trúc dsach liên kết
template <class Y>
class LinkedList{
    private:
        Node<Y>* head;
        Node<Y>* tail;
        int count;
    public:
    //danh sách rỗng
        LinkedList(){
            this->head = nullptr;
            this->tail = nullptr;
            this->count = 0;
        }
    //Hàm hủy
    ~LinkedList(){
        this->clear();
    }
    //Lấy phần tử đầu tiên
    Node<Y>* getHead() const{ //con trỏ Node đang chứa dữ liệu kiểu Y
        return this->head;
    }
    //thêm 1 đối tượng vào cuối dsach
    void addTail(Y newData){
        Node<Y>* newNode = new Node<Y>(newData);

        if(this->head == nullptr){
            this->head = newNode;
            this->tail = newNode;
        } else {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        this->count++;
    }
    //lấy số lượng 
    int getSize() const {
        return this->count;
    }
    //Dọn dẹp dsach
    void clear(){
        Node<Y>* current = this->head;
        while(current != nullptr){
            Node<Y>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
};
#endif