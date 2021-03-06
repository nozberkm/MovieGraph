/*
 * ActorGraph.cpp
 * Author: Nabi Ozberkman
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include "ActorGraph.hpp"

using namespace std;

ActorGraph::ActorGraph(void) {}


void ActorGraph::insert(string actorName, string movieName, int year, bool weighted) {
	unordered_map<string, Movie*>::iterator it;
	unordered_map<string, Actor*>::iterator it2;
	pair<unordered_map<string,Movie*>::iterator, bool> s;
	pair<unordered_map<string,Actor*>::iterator, bool> s2;
	movieName += ("#@" + to_string(year));
	if((it = this->databaseMovie.find(movieName)) == this->databaseMovie.end())	
	{		
		Movie* movieObject = new Movie(movieName, year, weighted);
		s = this->databaseMovie.insert(pair<string, Movie*> (movieName, movieObject));	
		it = s.first;
	}
	if((it2 = this->databaseActor.find(actorName)) != this->databaseActor.end()) {
		addFriend(it2->second, it->second);
		it->second->addActor(it2->second);
		//it2->second->addMovie(it->first);
	}
	else {
		s2 = this->databaseActor.insert(pair<string, Actor*> (actorName, new Actor(actorName)));
		it2 = s2.first;
		addFriend(it2->second, it->second);
		it->second->addActor(it2->second);
		//it2->second->addMovie(it->first);
	}
}

void ActorGraph::addFriend(Actor* actor, Movie* movie) {
	int movieWeight = movie->weight;
	vector<GraphEdge*> & friends = actor->friends;
	GraphEdge* current;
	auto it = movie->actors.begin();
	auto itE = movie->actors.end();
	while(it != itE) {
		current = new GraphEdge(actor, (*it), movie->name, movieWeight);
		friends.push_back(current);
		allEdges.push_back(current);
		(*it)->addEdge(current);
		it++;
	}
}


bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
	// Initialize the file stream
	ifstream infile(in_filename);
	//	ActorGraph* graph = new ActorGraph();
	if(use_weighted_edges)
		this->weighted = true;
	bool have_header = false;

	// keep reading lines until the end of file is reached
	while (infile) {
		string s;

		// get the next line
		if (!getline( infile, s )) break;

		if (!have_header) {
			// skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string> record;

		while (ss) {
			string next;

			// get the next string before hitting a tab character and put it in 'next'
			if (!getline( ss, next, '\t' )) break;

			record.push_back( next );
		}

		if (record.size() != 3) {
			// we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);

		this->insert(actor_name, movie_title, movie_year, use_weighted_edges);
		// we have an actor/movie relationship, now what?
	}

	if (!infile.eof()) {
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();
	//	this->buildAdjacent();
	return true;
}

void ActorGraph::buildAdjacent() {
	auto it = this->databaseActor.begin();
	auto itE = this->databaseActor.end();	
	Movie* currentMov;
	Actor* currentAct;
	while(it != itE) {
		currentAct = it->second;


	}
}
