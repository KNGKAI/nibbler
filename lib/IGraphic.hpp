#ifndef IGRAPHIC_H
#define IGRAPHIC_H

	#include "Vec.hpp"
	struct Color
	{
		float r, g, b, a;
	};

    // Command Queue
    typedef struct c_queue{
        char command;
        c_queue * next;
    } c_queue;

    class IGraphic{
        private:
             c_queue command;
        public:
            virtual void 	processInput() = 0;
            virtual void 	render() = 0;

			virtual void 	DrawSquare(int, int, const Color&) = 0;
			virtual int		GetWidth() const = 0;
			virtual int		GetHeight() const = 0;
    };

#endif
