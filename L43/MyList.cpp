#include <iostream>

typedef struct s_my_list
{
    char c;
    struct s_my_list *before;
    struct s_my_list *next;
}   t_my_list;

class MyList
{
    t_my_list *first;
    t_my_list *last;

public:

    MyList()
    {
        first = new t_my_list;
        first->before = NULL;
        first->next = NULL;
        last = first;
    }

    void push_back(char c)
    {
        last->c = c;
        last->next = new t_my_list;
        t_my_list *tmp = last;
        last = last->next;
        last->before = tmp;
        tmp->next = last;
    }

    void insert(int pos)
    {
        t_my_list *tmp = getElem(pos);
        if (tmp)
        {
            tmp->before->next = tmp->next;
            tmp->next->before = tmp->before;
            delete tmp;
        }
    }

    char returnElem(int pos)
    {
        t_my_list *tmp = getElem(pos);
        char c = 0;
        if (tmp)
            c = tmp->c;
        return c;
    }

private:

    t_my_list *getElem(int pos)
    {
        t_my_list *tmp = first;
        for (int i = 0; i < pos; i++)
        {   
            if (tmp == last)
                return NULL;
            tmp = tmp->next;
        }
        return tmp;
    }
};