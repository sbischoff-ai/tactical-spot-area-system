#ifndef SESSION_H
#define SESSION_H

class Map;

class Session
{
public:
	Session();
	~Session();

protected:
	Map* maps;
	Map* activeMap;
	int turn;
};

#endif // SESSION_H