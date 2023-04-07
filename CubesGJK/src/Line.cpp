#include "Line.h"

void Line::drawLine(glm::vec3 A, glm::vec3 B)
{
	glBegin(GL_LINES);
	glVertex3f(A.x, A.y, A.z);
	glVertex3f(B.x, B.y, B.z);
	glEnd();
}
