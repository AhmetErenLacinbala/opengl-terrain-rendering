#include "vertexArrayObject.hpp"
#include "vertexTypes.hpp"
#include <GL/glew.h>


VertexArrayObject::VertexArrayObject(){

     m_VaoId = 0;
     m_VboId = 0;
     m_IboId = 0;


}

void VertexArrayObject::build(const Vertex3TexList& vertices, const IndexList& indices){
	glGenVertexArrays(1, &m_VaoId); 

    glGenBuffers(1,&m_VboId);

    glGenBuffers(1, &m_IboId);
   
    glBindVertexArray(m_VaoId);
    
    glBindBuffer(GL_ARRAY_BUFFER,m_VaoId);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex3Tex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
       
    glEnableVertexAttribArray(0); 
    //kaplama bilgileri belirtiliyor.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(1);    
    
    //daireye ait index değerleri index buffer'a kopyalanıyor.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW); 

    m_AttribList.push_back(0);
    m_AttribList.push_back(1);
}

void VertexArrayObject::deactivate(){
glBindVertexArray(m_VaoId);
    for(auto next:m_AttribList )
        glEnableVertexAttribArray(next);
}

void VertexArrayObject::activate(){
for(auto next:m_AttribList )
        glDisableVertexAttribArray(next);
    glBindVertexArray(0);
}
