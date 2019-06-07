/*
    UCR Spring 2019
    CS 133 Lab 9 - Voronoi Region
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

struct point {
    int x;
    int y;
};

typedef Vertex* PVertex;
typedef HalfEdge* PEdge;
typedef Face* PFace;
typedef struct point Point;

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

    Point computeVoronoiVertex(PEdge e1, PEdge e2) {
	// Assuming that e1 and e2 are any half edges adjacent to the vertex:
	Point p;

        if ((e1->origin == e2->origin) || (e1->origin == e2->twin->origin) ||
	(e1->twin->origin == e2->origin) || (e1->twin->origin == e2->twin->origin)) {
            p.x = e1->origin->x;
	    p.y = e1->origin->y;
	}

	return p;
    }
};


int main() {

    DCEL dcel;
    PVertex v1 = dcel.createVertex(1,1);
    PVertex v2 = dcel.createVertex(5,1);
    PVertex v3 = dcel.createVertex(3,4);
    PVertex v4 = dcel.createVertex(3,2);

    PEdge e1;  PEdge e2;  PEdge e3;  PEdge e4;  PEdge e5;  PEdge e6;
    PEdge e7;  PEdge e8;  PEdge e9;  PEdge e10;  PEdge e11;  PEdge e12;

    PFace f0;  PFace f1; PFace f2; PFace f3;

    e1->origin = v1;
    e1->face = f1;
    e1->twin = e2;
    e1->next = e8;

    e2->origin = v2;
    e2->face = f0;
    e2->twin = e1;
    e2->next = e6;

    e3->origin = v2;
    e3->face = f2;
    e3->twin = e4;
    e3->next = e9;

    e4->origin = v3;
    e4->face = f0;
    e4->twin = e3;
    e4->next = e2;

    e5->origin = v3;
    e5->face = f3;
    e5->twin = e6;
    e5->next = e11;

    e6->origin = v1;
    e6->face = f0;
    e6->twin = e5;
    e6->next = e4;

    e7->origin = v4;
    e7->face = f2;
    e7->twin = e8;
    e7->next = e3;

    e8->origin = v2;
    e8->face = f1;
    e8->twin = e7;
    e8->next = e12;

    e9->origin = v3;
    e9->face = f2;
    e9->twin = e10;
    e9->next = e7;

    e10->origin = v4;
    e10->face = f3;
    e10->twin = e9;
    e10->next = e5;

    e11->origin = v1;
    e11->face = f3;
    e11->twin = e12;
    e11->next = e10;

    e12->origin = v4;
    e12->face = f1;
    e12->twin = e11;
    e12->next = e1;

    f0->edge = e6;
    f1->edge = e1;
    f2->edge = e3;
    f3->edge = e5;

    Point vert = dcel.computeVoronoiVertex(e1, e6);
    cout << vert.x << ", " << vert.y << endl;
}
