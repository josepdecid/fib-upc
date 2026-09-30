# IDI - LABS

## Bloc 1

### S1

#### Exercici 1
Modificar les coordenades de cada vèrtex a la funció createBuffers().

#### Exercici 2
Incrementar el tamany del vector de Vèrtexs, afegir els nous (regla mà dreta). A la funció glDrawArrays indicar el nombre de vèrtexs a pintar.
Per a fer-ho amb Strips, canviem el mètode de pintar de glDrawArrays a GL_TRIANGLE_STRIP passant només 4 vèrtexs A-B-C-D que formaran els triangles A-B-C i B-C-D.

#### Exercici 3
Dibuixarem la casa amb 3 triangles, 2 que formen el quadrat i un altre per a la teulada, amb 9 vèrtexs.
Per fer-ho amb triangle-strip, necessitem 4 vèrtexs que formin triangles de la casa

#### Exercici 4
Hem de definir un nou VAO i VBO al MyGLWidget.h, llavors dupliquem el codi del paintGL() per als dos VAO, i el codi de createBuffers per als dos VAO/VBO.

### S2

#### Exercici 1
Modificar el fragment shader per dividir en quadrants i assignar colors diferents a cada un.

#### Exercici 2
Per pintar a ratlles horitzontals només cal modificar el fragment shader per a que apliqui els colors en seccions parells parells per exemple.

#### Exercici 3
Només cal multiplicar el vèrtex per 0.5, que produeix l'efecte de fer més petita la figura.

#### Exercici 4
Hem de posar un color d'entrada al vertex shader que el treu amb rgba. Al fragmend shader l'assigna al fragment color. Hem de definir un colorLoc i un VBO_Color al MyGLWidget.h i al .cpp associar el location, definir un vector de colors i assignar-los a cada vèrtex

## Bloc 2

### S1

#### Exercici 1
Afegim un uniform al vertex shader, definim un location al .h i li assignem l'unfirom amb el mateix nom al .cpp
Creem una funció que defineix la perspectiva de la càmara, i la cridem al init.

#### Exercici 2
Afegim un uniform al vertex shader, definim un location al .h i li assignem l'unfirom amb el mateix nom al .cpp
Creem una funció que col·loca la càmara, i la cridem al init.

#### Exercici 3
Canviant el vector up fem que la casa miri cap a dalt, dreta...

#### Exercici 4
Declarem un VAO per al Homer i dos VBO un per als vèrtexs i l'altre per als colors. Abans de crear els buffers, carreguem el model i activem el Z-buffer amb glEnable(GL_DEPTH_TEST), també fent clear del GL_DEPTH_BUFFER_BIT al paintGL. Els triangles a pintar són del triangle 0 a model.faces().size() * 3, ja que cada triangles té 3 costats. Al createBuffers, inicialitzem el VBO amb tamany sizeof(GLfloat) * m.faces().size() * 3 * 3, ja que cada cara, té tres triangles de tres components cadascun, del tipus float. S'ha d'incloure el model i model.h al .pro i .h.

#### Exercici 5
Definim una variable rotation que augmenta valor cada cop que premem la tecla R i cridem a modelTransform();

#### Exercici 6
Creem un nou VAO i dos VBO per al terra, un per als vèrtexs i l'altre per als colors de cada un. Creem dos triangles per fer un plà.

### S2

#### Exercici 1
Cada cop que es redimensiona la pantalla, s'invoca resizeGL, llavors cridem a projectTransform, on calculem la relació d'aspecte del window width/height.
Calculem alpha segons la ra. Si es normal serà 45º, en cas contrari l'arctan de 45/ra.

#### Exercici 2
Creem tots els valors de znear, zfar, OBS, VRP, VUP, angle que necessitem per al càlcul de la matriu mínima. Englobem les duncions viewTransform i projectTransform dins d'una d'inicialitzar càmera, que càlcula tots els paràmetres necessaris.

#### Exercici 3
A les funcions de viewTransform i projectTransform, apliquem els valors calculats anteriorment.

#### Exercici 4
Eliminem el terra, canviem model per Patricio, i calculem nova caixa contenidora a partir del model.

#### Exercici 5
Afegim al viewTransform els càlculs per als angles d'Euler.

#### Exercici 6
Afegim moviment de ratolí, amb listeners per a clickar, desclickar, i moure, que modifica els angles d'Euler i crida a la viewTransform.

### S3

#### Exercici 1
Afegim un deltaZoom per a ponderar el nivell de zoom i dos listeners de teclat a X i Z per a modificar el FOV, i un altre al botó dret del ratolí.
Després del event del listener, hem de forçar a cridar projectTransform.

#### Exercici 2
Carreguem un segon model de Patricio i afegim el terra. Calculem el centre del patricio amb el terra com a base i el traslladem allà. Llavors apliquem la rotació (només en un) traslació i finalment escalat, en ordre invers al que ho volem.

#### Exercici 3
Per a canviar a vista ortogonal, només cal canviar la càmera al projectTransform, per
glm::mat4 Proj = glm::ortho(-4.0f, 4.0f, -4.0f, 4.0f, znear, zfar);

#### Exercici 4

designer MyForm.ui &
