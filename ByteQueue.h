#ifndef __BYTEQUEUE__
#define __BYTEQUEUE__
#include <list>
#include <string.h>
#include "xstring.h"

class ByteQueue : public std::list<char>
{
private:
	size_t count;
	long long total;
public:
	ByteQueue(void):count(0),total(0)
	{
	}
	const size_t Count(void)const
	{
		return count;
	}
	const long long GetTotal(void)const
	{
		return total;
	}
	void Push(const char *buf, const int len)
	{
		for(int i = 0; i < len && buf; i++)
		{
			push_back(buf[i]);
			count += 1;
			total += 1LL;;
		}
	}
	bool Peek(char *buf, int len)
	{
		int i = 0;

		if(buf || count >= len)
		{
			iterator x = begin();
			for(i = 0; i < len; i++,x++)
			{
				buf[i] = *x;
			}
		}
		return (i == len);
	}
	void Pop(int len)
	{
		for(int i = 0; i < len; i++)
		{
			pop_front();
			count--;
		}
	}
	int ToInt(void)
	{
		if(count > 3)
		{
			iterator x = begin();
			return ((*x++) << 24) 
				|  ((*x++) << 16) 
				|  ((*x++) << 8) 
				|  ((*x++) << 0);
		}
		return 0;
	}
	const xstring ToString(void)
	{
		xstring s;
		for(iterator i = begin(); i != end(); i++)
		{
			s += xstring("[%02X]", (unsigned char)*i);
		}
		return s;
	}
};

#endif//__BYTEQUEUE__
