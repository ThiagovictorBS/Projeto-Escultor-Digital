#ifndef SCULPTOR_H
#define SCULPTOR_H

struct Voxel{
    /**
     * @brief Cores. r para cor vermelho. g para cor verde. b para cor azul.
     */
    float r,g,b; // Colors
    /**
     * @brief a é a transparência.
     */
    float a; // Transparency
    /**
     * @brief isOn é um booleano que classifica o bloco como "existente" ou não.
     */
    bool isOn; // Included or not
};
/**
 * @brief The Sculptor class é a classe que serve para criar esculturas por meio de blocos dispostos em 3 dimensões.
 */
class Sculptor{
private:
    /**
       * @brief v é a matriz 3d
       */
      Voxel ***v; // 3D matriz
      /**
       * @brief nx, ny, nz são as dimensões para o eixo x, y e z, respectivamente.
       */
      int nx,ny,nz; // Dimensões
      /**
       * @brief r, g e b são as cores e a é a transparência do bloco.
       */
      float r,g,b,a; // Cor
public:
      /**
       * @brief Sculptor é o construtor que cria o espaço de "desenho" em 3d.
       * @param _nx é o tamanho do eixo x.
       * @param _ny é o tamanho do eixo y.
       * @param _nz é o tamanho do eixo z.
       */
      Sculptor(int _nx, int _ny, int _nz);
      ~Sculptor();
      /**
       * @brief setColor é a função que vai definir as cores e transparência dos próximos blocos.
       * @param r
       * @param g
       * @param b
       * @param alpha
       */
      void setColor(float r, float g, float b, float alpha);
      /**
       * @brief putVoxel é a função que põe os blocos.
       * @param x é a posição em x.
       * @param y é a posição em y.
       * @param z é a posição em z.
       */
      void putVoxel(int x, int y, int z);
      /**
       * @brief cutVoxel é a função que remove os blocos.
       * @param x é a posição em x.
       * @param y é a posição em y.
       * @param z é a posição em z.
       */
      void cutVoxel(int x, int y, int z);
      /**
       * @brief putBox é a função que insere blocos em determinados intervalos.
       * @param x0 é a posição inicial em x.
       * @param x1 é a posição final em x.
       * @param y0 é a posição inicial em y.
       * @param y1 é a posição final em y.
       * @param z0 é a posição inicial em z.
       * @param z1 é a posição final em z.
       */
      void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
      /**
       * @brief cutBox é a função que remove blocos em determinados intervalos.
       * @param x0 é a posição inicial em x.
       * @param x1 é a posição final em x.
       * @param y0 é a posição inicial em y.
       * @param y1 é a posição final em y.
       * @param z0 é a posição inicial em z.
       * @param z1 é a posição final em z.
       */
      void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
      /**
       * @brief putSphere é a função que cria uma esfera de blocos.
       * @param xcenter é a posição central em x.
       * @param ycenter é a posição central em y.
       * @param zcenter é a posição central em z.
       * @param radius é o raio da esfera.
       */
      void putSphere(int xcenter, int ycenter, int zcenter, int radius);
      /**
       * @brief cutSphere é a função que retira uma esfera de blocos.
       * @param xcenter é a posição central em x.
       * @param ycenter é a posição central em y.
       * @param zcenter é a posição central em z.
       * @param radius é o raio da esfera.
       */
      void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
      //void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
      //void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
      /**
       * @brief writeOFF é a função que imprime os dados dos blocos em formato OFF.
       * @param filename é o nome que o arquivo irá receber.
       */
      void writeOFF(char* filename);
};

#endif // SCULPTOR_H
