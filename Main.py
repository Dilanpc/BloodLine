import pygame, sys, random
from Resours import archivoMapa, geometry



pygame.init()
pygame.mixer.init()
clock = pygame.time.Clock()
running = True

#SCREEN
screen_width = 1320
screen_height = 720
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("POO")


#Variables
sujetos = []
cj = None
enemies = []
dead_enemies = 0
difficulty = 1

class Person:
    def __init__(self, color, velocidad, pos:tuple, arma) -> None:
        self.img = pygame.Surface((20,20))
        self.img.fill(color)
        self.rect = self.img.get_rect()
        self.rect.topleft = pos
        self.color = color
        self.velocidad = velocidad
        self.arma = Gun(*arma)
        self.life = 100

    def mostrar(self):
        screen.blit(self.img, self.rect)

    def shoot(self, destino):
        if self.arma.ciclo == 0 and self.arma.cargador > 0 and not self.arma.reloading:
            balas.append(Bullet(self, destino))
            self.arma.ciclo = 1
            self.arma.cargador -= 1
    
    def recharge(self):
        arma = self.arma
        if arma.reloading != 0: #Si está recargando
            pass
        elif arma.cargador == arma.cargadorMax: #Si está lleno el cargador
            pass
        elif arma.totalBalas == 0 and isinstance(self, Jugador): #Si no tiene balas, si es enemigo tiene infinitas
            pass
        else:    
            arma.reloading = 1
            #Sonido recargar...

    def hit(self, damge):
        self.life -= damge
        if self.life <= 0:
            global dead_enemies
            dead_enemies += 1
            

class Jugador(Person):

    def __init__(self, color, velocidad, pos, arma:object) -> None:
        super().__init__(color, velocidad, pos, arma)

    def mover(self, direction:tuple, currentMap):
        move = [0,0]
        if direction[0] == 0 or direction[1] == 0:

            move[0] = direction[0] * self.velocidad
            move[1] = direction[1] * self.velocidad


        else:
            move = geometry.porEscalar(1/geometry.norma(direction)*self.velocidad, direction)

        self.rect.center = geometry.suma(self.rect.center, move)

        s=False
        for i in range(len(currentMap.rects)):
            s = s or self.rect.colliderect(currentMap.rects[i])
            if s:
                self.rect.center = geometry.suma(self.rect.center, geometry.porEscalar(-1,move))
                break
        
            
class Enemy(Person):
    def __init__(self, color, velocidad, pattern:list, arma: list, ciclico = True) -> None:
        
        super().__init__(color, velocidad, pattern[0], [*arma, True])
        self.pattern = MovePattern(pattern, ciclico) #Lista de puntos a los que debe ir el sujeto
        self.direction = self.get_direction()
        


    def shoot(self):
        super().shoot(cj.rect.center)
        if self.arma.cargador == 0:
            self.recharge()


    def mover(self):
        #comprobar si ya está en el punto
        vector = geometry.resta(self.pattern.current_point(), self.rect.center)
        if geometry.norma(vector) < 10:
            self.pattern.inicio = self.rect.center
            self.pattern.next_point()
            self.direction = self.get_direction()
            
        
        aumento = geometry.porEscalar(self.velocidad * self.pattern.ciclo_move, self.direction)
        self.rect.center = geometry.suma(self.pattern.inicio, aumento)
        self.pattern.ciclo_move +=1

    def get_direction(self):
        return direction(self.rect.center, self.pattern.current_point())
        
    


class MovePattern():
    def __init__(self, lista, ciclico) -> None:
        self.lista = lista
        self.ciclo_move = 0
        self.in_list = 0
        self.sentido = 1
        self.ciclico = ciclico
        self.inicio = lista[0]


    def next_point(self):
        self.in_list += self.sentido
        self.ciclo_move = 0
        if self.ciclico:
            if self.in_list == len(self.lista):
                self.in_list = 0

        else: #Ida y vuelta
            if self.in_list == len(self.lista)-1:
                self.sentido = -1
            elif self.in_list == 0:
                self.sentido = 1

    def current_point(self) -> list:
        return self.lista[self.in_list]


balas = []

class Bullet:
    def __init__(self, tirador:object, destino:tuple):
        self.img = pygame.image.load("Resours/bullet.png")
        self.rect = self.img.get_rect(center = tirador.rect.center)
        self.velocidad = tirador.arma.velocidad
        self.tirador = tirador
        self.inicio = tirador.rect.center
        
        #desface si es enemigo:
        multiplicador = 1
        if isinstance(tirador, Enemy):
            multiplicador = 10/difficulty

        self.direction = self.get_direction(destino)
        self.damage = tirador.arma.damage
        self.color = (249, 224, 53)
        self.ciclo = 0
        #El ciclo se utiliza porque se manejan vectores con componentes no enteras. Si solo se suma el vector dirección, entonces se aproximará al entero más cercano; por ello no sería muy preciso.
        
    def get_direction(self, destino):
        vectorNormal = direction(self.rect.center, destino)
        dispersion = self.tirador.arma.dispersion
        #Error de enemigo
        multiplicador = 1
        if isinstance(self.tirador, Enemy):
            multiplicador = 10 / difficulty
        anguloError = random.randint( *geometry.porEscalar(multiplicador, (-dispersion, dispersion))   )

        return geometry.rotacion(vectorNormal, anguloError)

    def update(self):
        self.rect.center = geometry.suma(self.inicio, geometry.porEscalar(self.ciclo * self.velocidad, self.direction))
        self.ciclo += 1
    

    def mostrar(self):
        #screen.blit(self.img, self.rect)
        pygame.draw.circle(screen, self.color, self.rect.center, 4)



class Gun:
    def __init__(self, cadencia:int, velocidad:float, damage:float, totalBalas:int, cargadorMax:int, rechargeTime:int, dispersion, balas_infinitas = False):
        self.cadencia = cadencia
        self.velocidad = velocidad
        self.damage = damage
        self.totalBalas = totalBalas
        self.cargadorMax = cargadorMax
        self.cargador = cargadorMax
        self.rechargeTime = rechargeTime
        self.dispersion = dispersion
        self.ciclo = 0
        self.reloading = 0
        self.__balas_infinitas = balas_infinitas


    def recharge(self):

        if self.reloading == self.rechargeTime:
            if self.totalBalas >= self.cargadorMax:
                self.totalBalas -= (self.cargadorMax - self.cargador) * (0 if self.__balas_infinitas else 1)
                self.cargador = self.cargadorMax
            

            else:
                self.cargador = self.cargador + self.totalBalas
                self.totalBalas -= self.totalBalas * (0 if self.__balas_infinitas else 1)

            self.reloading = 0

        else : 
            self.reloading += 1


#0: Periodo, 1: velocidad, 2: damage, 3: totalBalas, 4: cargadorMax, 5: rechargeTime, 6: dispersión
pistol = [18, 20, 12, 40, 8, 120, 5]
m16 = [14, 20, 20, 200, 20, 120, 0]
metralleta = [8, 20, 10, 200, 100, 300, 10]

class Mapa:
    def __init__(self, numeroMapa) -> None:
        self.__iniciar_mapa(numeroMapa)

        self.oppened_doors = [True, False, False]
        self.exit_door = False
    
    def get_rect(self) -> list:
        optimizado = []
        visited = set()
        n = len(self.matrix)
        m = len(self.matrix[0])
        cuadriculaAncho = self.cuadriculaAncho
        cuadriculaAlto = self.cuadriculaAlto
        for i in range(n):
            for j in range(m):
                if self.matrix[i][j] and not (i, j) in visited:
                    visited.add((i,j))
                    ancho = 1
                    alto = 1

                    k=1
                    while  not (i, j+k) in visited and j+k<m: #Expandir hacia la derecha
                        if self.matrix[i][j+k]:
                            ancho +=1
                            k +=1
                        else:
                            break

                    k=1
                    z = True
                    while z and i+k<n: #expandir hacia abajo

                        for l in range(ancho):
                            z = z and self.matrix[i+k][j+l]
                        
                        if z:
                            alto +=1
                            k+=1

                    for al in range(alto): #alctualziar visited
                        for  an in range(ancho):
                            visited.add((i+al, j+an))

                    optimizado.append([(j*cuadriculaAncho, i*cuadriculaAlto), (ancho*cuadriculaAncho, alto*cuadriculaAlto)])

        rects = []
        for h in range(len(optimizado)): #convertir a Rects
            rects.append(pygame.Rect(optimizado[h]))
        
        return rects

    def del_enemies(self):
        global sujetos
        enemies.clear()
        sujetos = [cj]


    def add_enemies(self):
        for i in range(len(self.info_enemy)):
            enemies.append(Enemy(*self.info_enemy[i]))
            sujetos.append(enemies[i])


    def mostrar(self):
        screen.blit(fondo, (0,0))
        for i in range(len(self.rects)):
            pygame.draw.rect(screen, (90,90,90), self.rects[i])

    def __iniciar_mapa(self, numeroMapa):

        self.matrix = archivoMapa.bringMap(numeroMapa)
        self.cuadriculaAncho = screen_width//len(self.matrix[0])
        self.cuadriculaAlto = screen_height//len(self.matrix)
        self.rects = self.get_rect()
        self.numero = numeroMapa
        self.info_enemy = archivoMapa.get_info(numeroMapa)
        self.del_enemies()
        self.add_enemies()
        self.add_door()


    def accederMapa(self):
        global dead_enemies
        if not cj.rect.left > screen_width:
            if dead_enemies == len(enemies) and self.exit_door == False and self.numero != 0:
                self.del_door()
                self.exit_door = True
        else:
            if self.numero == 0:

                if  19 < cj.rect.top < 81:
                    self.__iniciar_mapa(1)

                elif 99 < cj.rect.top < 181:
                    self.__iniciar_mapa(2)

            else:
                self.__iniciar_mapa(0)

            cj.rect.right = 10
            self.exit_door = False
            dead_enemies = 0
            balas.clear()
    

    def coordenada_a_matriz(self, coordenada):
        columna = coordenada[0]//self.cuadriculaAncho
        fila = coordenada[1]//self.cuadriculaAlto
        return (fila,columna)

    def add_door(self):
        if not self.numero == 0: #Si no es la base
            self.rects.append( pygame.Rect(61*self.cuadriculaAncho, 31*self.cuadriculaAlto, self.cuadriculaAncho, self.cuadriculaAlto*4 ))
    
    def del_door(self, nivel=None):
        if nivel == None: #Si no es la base
            self.rects.remove(pygame.Rect(61*self.cuadriculaAncho, 31*self.cuadriculaAlto, self.cuadriculaAncho, self.cuadriculaAlto*4 ))





class Text:
    def __init__(self, text:str, font:int, size:int, color:tuple, topleft:tuple=None) -> None:
        self.__text = text
        self.__color = color
        self.__size = size
        self.__fuente= font
        self.pos = topleft
        self.__define()
        if topleft != None:
            self.rect.topleft = topleft
    
    def __define(self):
        self.font = pygame.font.Font(self.__fuente, self.__size)
        self.render = self.font.render(self.__text, 1, self.__color)
        self.rect = self.render.get_rect(topleft = self.pos)

    def set_text(self, text:str):
        self.__text = text
        self.render = self.font.render(self.__text, 1, self.__color)
        self.rect = self.render.get_rect(topleft = self.pos)

    def set_font(self, font=None, size=None, color=None):

        if size != None:
            self.__size = size

        if color != None:
            self.__color = color

        if font != None:
            self.__fuente = font
        
        self.__define()
        
    def get_text(self):
        return self.__text
    def get_color(self):
        return self.__color
    def get_size(self):
        return self.__size
    def get_font(self):
        return self.__fuente


    def mostrar(self, topleft=None):
        if topleft != None:
            self.pos = topleft
            self.rect.topleft = topleft
        
        screen.blit(self.render, self.rect)





def direction(start, end):
    v = geometry.vector(start,end)
    return geometry.porEscalar(1/geometry.norma(v), v)


def actualizarBalas():
    for bal in balas:
        bal.update()

        choque = False
        for rect in currentMap.rects: #Choque con pared
            choque = choque or rect.collidepoint(bal.rect.center)
            if choque:
                balas.remove(bal)
                break

        if choque:
            pass

        elif bal.ciclo > 100:
            balas.remove(bal)

        else:
            bal.mostrar()
            for sujeto in sujetos: #Choque con sujeto
                if not bal.rect.colliderect(sujeto.rect):
                    pass
                elif not bal.tirador != sujeto:
                    pass
                else:
                    balas.remove(bal)
                    sujeto.hit(bal.damage)
                    sujeto.life -= bal.damage
                    if not sujeto.life > 0:
                        sujetos.remove(sujeto)


def actualizarSujetos():
    for sujeto in sujetos: #tiempo de espera durante disparo
        if sujeto.arma.cadencia <= sujeto.arma.ciclo:
            sujeto.arma.ciclo = 0
        elif sujeto.arma.ciclo != 0:
            sujeto.arma.ciclo += 1
        
        if sujeto.life > 0: #mostrar vivos
            sujeto.mostrar()
            if isinstance(sujeto, Enemy):
                sujeto.mover()
                sujeto.shoot()

def actualizarRecarga():
    for sujeto in sujetos:
        if sujeto.arma.reloading: #Si está recargando
            sujeto.arma.recharge()






#FONDO
fondo = pygame.Surface((screen_width, screen_height))
currentMap = Mapa(0)

#SUJETOS
cj = Jugador((0,200,50), 6, (20,40), m16) 
#enemy = Enemy((200,0,0), 3, [(200,200), (600,600), (600, 200)], m16)
#enemies.append(enemy)

sujetos = [cj, *enemies]


#HUD
txtBalas = Text("", None, 30, "white", (10,10))


clic =False


#--------------------------------------------------------------------------------------------------------------
while running:
    clock.tick(60)
    currentMap.mostrar()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            clic = True
            #print(currentMap.coordenada_a_matriz(pygame.mouse.get_pos()))
            
            
        if event.type == pygame.MOUSEBUTTONUP:
            clic=False



    key = pygame.key.get_pressed()    
    dir = (0,0)
    if key[pygame.K_d]:
        dir = geometry.suma(dir, (1,0))
    if key[pygame.K_w]:
        dir = geometry.suma(dir, (0,-1))
    if key[pygame.K_a]:
        dir = geometry.suma(dir, (-1,0))
    if key[pygame.K_s]:
        dir = geometry.suma(dir, (0,1))
    
    cj.mover(dir, currentMap)



    if clic:
        cj.shoot(pygame.mouse.get_pos())
        
    
    if key[pygame.K_r]:
        cj.recharge()
    




        
#HUD
    txtBalas.set_text(str(cj.arma.cargador) + "/" + str(cj.arma.cargadorMax) +" - "+ str(cj.arma.totalBalas))
    txtBalas.mostrar()

    actualizarBalas()
    
    actualizarRecarga()

    actualizarSujetos()
    
    currentMap.accederMapa()

    #enemy.shoot()

    



    pygame.display.flip()

print(m16)

pygame.quit()
sys.exit()

