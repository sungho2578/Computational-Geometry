/*
    UCR Spring 2019
    CS 133 Lab 8 - DCEL
    Sungho Ahn, 862026328
*/

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

struct HalfEdge;

struct Vertex {
    HalfEdge* leaving;
    double x, y;

    HalfEdge* nextLeaving(HalfEdge*);
};

struct Face {
    HalfEdge* edge;

    vector<HalfEdge*> getBoundary();
};

struct HalfEdge {
    Vertex* origin;
    Face* face;
    HalfEdge* twin;
    HalfEdge* next;

    Vertex* destination();
};

typedef Vertex* PVertex;
typedef HalfEdge* PEdge;
typedef Face* PFace;

PEdge Vertex::nextLeaving(PEdge e) {
    return e->twin->next->twin;
}

PVertex destination() {
    HalfEdge* e;

    return e->twin->origin;
}

vector<PEdge> getBoundary() {
    vector<HalfEdge*> eList;
    HalfEdge* e;
    HalfEdge* tn = e->next;

    while (tn != e) {
	eList.push_back(tn);
	tn = tn->next;
    }

    return eList;
}

struct DCEL {

    PVertex createVertex(double x, double y) {
        Vertex* v = new Vertex;
        v->x = x;
        v->y = y;

        return v;
    }

    vector<PFace> findFaces(PVertex v) {
	vector<PFace> f;
        f.push_back(v->leaving->face);
        f.push_back(v->leaving->twin->next->twin->face);
        f.push_back(v->leaving->twin->face);
        f.push_back(v->leaving->twin->next->face);

        return f;
    }

    PFace findCommonFace(PVertex v1, PVertex v2) {
	if (v1->leaving->face == v2->leaving->face) {
	    return v1->leaving->face;
	}

	return NULL;
    }

    bool isConnected(PVertex v1, PVertex v2) {
	if ((v1->leaving->twin == v2->leaving) && (v2->leaving->twin == v1->leaving) &&
		(v1->leaving->next->origin == v2) && (v2->leaving->next->origin == v1) &&
			(v1->leaving->twin->origin == v2) && (v2->leaving->twin->origin == v1)) {
	    return true;
	}

	else {
	    return false;
	}
    }

    PEdge findIncidentEdge(PVertex v, PFace f) {
	if (v->leaving->face == f) {
	    return v->leaving;
	}

	else {
	    return NULL;
	}
    }

    PFace getUnboundedFace() {
	Face* f = new Face;

	return f;
    }

    PEdge createEdge(PFace f, PVertex v1, PVertex v2) {
        HalfEdge* e = new HalfEdge;
	e->origin = v1;
	e->twin->origin = v2;
	e->next->origin = v2;
	e->face = f;
	f->edge = e;

	return e;
    }

    PEdge splitFace(PFace f, PVertex v1, PVertex v2) {
	Face* f1 = new Face;
	Face* f2 = new Face;
	HalfEdge* e1 = new HalfEdge;
	HalfEdge* e2 = new HalfEdge;
	e1->origin = v1;
	e1->twin = e2;
	e1->twin->origin = v2;
	e1->next->origin = v2;
	e1->face = f1;
	e2->origin = v2;
	e2->twin = e1;
	e2->twin->origin = v1;
	e2->next->origin = v1;
	e2->face = f2;

	return e1;
    }
};

int main() {

    DCEL dcel;
    PVertex v1 = dcel.createVertex(1,0);
    PVertex v2 = dcel.createVertex(2,1);
    PVertex v3 = dcel.createVertex(0,1);
    PVertex v4 = dcel.createVertex(0,0);
    // v1 has one face (the unbounded face)
    assert(dcel.findFaces(v1).size() == 1);
    PEdge e1 = dcel.createEdge(dcel.getUnboundedFace(), v1, v2);
    // v1 still has one face which is not NULL
    assert(dcel.findFaces(v1).size() == 1);
    assert(dcel.findFaces(v1).front() != NULL);
    // v2 also has one unbounded face
    assert(dcel.findFaces(v2).size() == 1);
    // All vertices have one common face which is the unbounded face
    assert(dcel.findCommonFace(v1, v2) != NULL);
    assert(dcel.findCommonFace(v1, v3) != NULL);
    // Find the newly created edge using the findIncidentEdge function
    assert(dcel.findIncidentEdge(e1->origin, e1->face) == e1);
    dcel.createEdge(dcel.getUnboundedFace(), v2, v3);
    // v1 and v2 are still connected
    assert(dcel.isConnected(v1, v2));
    // v1 and v3 are not connected (i.e., not adjacent)
    assert(!dcel.isConnected(v1, v3));
    // Create two new edges to create the first face
    dcel.createEdge(dcel.getUnboundedFace(), v3, v4);
    dcel.splitFace(dcel.getUnboundedFace(), v4, v1);
    // Now there are two faces, the newly created face and the unbounded face
    // All the four vertices are adjacent to the two faces
    assert(dcel.findFaces(v1).size() == 2);
    assert(dcel.findFaces(v2).size() == 2);
    assert(dcel.findFaces(v3).size() == 2);
    assert(dcel.findFaces(v4).size() == 2);
    // v1 and v2 have two common faces, but the bounded face should be returned
    assert(dcel.findCommonFace(v1, v2) != dcel.getUnboundedFace());
    // Create a new edge that will result in a new face
    dcel.splitFace(dcel.findCommonFace(v1, v2), v4, v2);
    assert(dcel.findFaces(v4).size() == 3);
}
