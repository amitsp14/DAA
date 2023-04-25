#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 #include "<adjacency_list.h>"
 #include "heap.h"
/* Represents an edge (has both sides, represented as vnode) and the edge weight. */
typedef struct prim_edge_nodes_
{
    vertex_node *vnodeA;
    vertex_node *vnodeB;
    int weight; /* Weight of the link. */
} prim_edge_nodes;

int prim_heap_compare(const void *value1, const void *value2)
{
    prim_edge_nodes *node1 = (prim_edge_nodes *)value1;
    prim_edge_nodes *node2 = (prim_edge_nodes *)value2;

    if (node1->weight < node2->weight)
    {
        return -1;
    }
    else if (node1->weight > node2->weight)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void prim_heap_print(heap_t *heap)
{
    prim_edge_nodes *node, *parent_node;
    int counter = 0;

    printf("Printing the Heap: \n");
    if ((heap == NULL) || (heap->heap_current_size == 0))
    {
        printf("Heap is Empty\n\n");
        return;
    }

    for (counter = 0; counter < heap->heap_current_size; counter++)
    {
        node = (prim_edge_nodes *)heap->heap_array[counter];
        parent_node = (prim_edge_nodes *)(heap->heap_array[(int)floor((double)(counter - 1) / 2)]);
        if (counter == 0)
        {
            printf("\t[i: %d] %2d-%2d (Weight: %2d Parent: NULL)\n",
                   counter, node->vnodeA->val, node->vnodeB->val, node->weight);
        }
        else
        {
            printf("\t[i: %d] %2d-%2d (Weight: %2d Parent: %d-%d)\n",
                   counter,
                   node->vnodeA->val, node->vnodeB->val, node->weight,
                   parent_node->vnodeA->val, parent_node->vnodeB->val);
        }
    }
    printf("\n");
}

void prim_add_my_edges_to_heap(vertex_node *vnode, heap_t *heap)
{
    edge_node *enode;
    prim_edge_nodes *both_enodes;

    if (!vnode)
    {
        return;
    }

    for (enode = vnode->list_enode; enode != NULL; enode = enode->next_enode)
    {
        if (!(((vertex_node *)enode->parent_vnode)->color == COLOR_WHITE))
        {
            continue;
        }

        both_enodes = (prim_edge_nodes *)malloc(sizeof(prim_edge_nodes));
        if (!both_enodes)
        {
            return;
        }
        both_enodes->vnodeA = vnode;
        both_enodes->vnodeB = enode->parent_vnode;
        both_enodes->weight = enode->weight;
        heap_add(heap, (void *)both_enodes);
    }
}

void prim_run(vertex_node *graph_root, heap_t *heap)
{
    prim_edge_nodes *both_enodes, *both_enodes_prev;
    vertex_node *vnode, *new_vnode, *old_vnode;
    int err;

    if (!graph_root || !heap)
    {
        return;
    }

    /* Start by coloring all vertices as white. */
    for (vnode = graph_root; vnode != NULL; vnode = vnode->next_vnode)
    {
        vnode->color = COLOR_WHITE;
    }

    prim_add_my_edges_to_heap(graph_root, heap);
    graph_root->color = COLOR_BLACK;

    while (heap->heap_current_size)
    {
        /* Print the Heap */
        adjlist_print(graph_root);
        prim_heap_print(heap);

        /* Extract the Minimum */
        both_enodes = (prim_edge_nodes *)heap_extract(heap, &err);

        /* Find the unmarked vertex. Add its edges to Heap. */
        if ((both_enodes->vnodeA) && (both_enodes->vnodeA->color == COLOR_WHITE))
        {
            new_vnode = both_enodes->vnodeA;
            old_vnode = both_enodes->vnodeB;
        }

        if ((both_enodes->vnodeB) && (both_enodes->vnodeB->color == COLOR_WHITE))
        {
            new_vnode = both_enodes->vnodeB;
            old_vnode = both_enodes->vnodeA;
        }

        /* This vertex would be added to MST. Mark it black. */
        if (new_vnode && old_vnode)
        {
            new_vnode->color = COLOR_BLACK;
            prim_add_my_edges_to_heap(new_vnode, heap);
            printf("[%s]Prim's Result: %d-%d (Weight: %d)\n",
                   __FUNCTION__, new_vnode->val, old_vnode->val, both_enodes->weight);
        }
        free(both_enodes);
        new_vnode = old_vnode = NULL;
    }
}

int main()
{
    heap_t heap;
    int vertices[] = {101, 237, 680, 280, 880};
    int edges[][3] = {{101, 680, 12}, {101, 237, 10}, {880, 680, 2}, {101, 280, 8}, {237, 880, 3}};
    vertex_node *graph_root = NULL; /* Root of the graph */
    vertex_node *vnode = NULL;
    int len, i;

    /* Initialize the heap. */
    heap_init(&heap, prim_heap_compare);

    /* Add the vertices. */
    len = sizeof(vertices) / sizeof(vertices[0]);
    for (i = 0; i < len; i++)
    {
        adjlist_add_vertex(&graph_root, vertices[i], NULL);
    }

    /* Add the edges. */
    len = sizeof(edges) / sizeof(edges[0]);
    for (i = 0; i < len; i++)
    {
        adjlist_add_edge(graph_root, edges[i][0], edges[i][1], edges[i][2]);
    }
    adjlist_print(graph_root);

    /* Run the Prim's Algorithm. */
    prim_run(graph_root, &heap);

    /* Done with the Adjacency List and Heap. Free them */
    adjlist_free(&graph_root);
}