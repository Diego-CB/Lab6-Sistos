import threading
import random
import time

# Cantidad de recursos inicial y ajustable
cantidad_recursos = 10

# Semáforo para controlar el acceso a los recursos
semaphore = threading.Semaphore()

# Cantidad de iteraciones ajustable
num_iteraciones = 5

# Cantidad de recursos a consumir en cada iteración (mejora del segundo programa)
cantidad_consumir = 2

# Método que ejecutan los threads
def consumir_recurso(thread_id):
    global cantidad_recursos

    for _ in range(num_iteraciones):
        # Consumir recursos
        semaphore.acquire()
        if cantidad_recursos >= cantidad_consumir:
            cantidad_recursos -= cantidad_consumir
            print(f"Thread {thread_id}: Consumió {cantidad_consumir} recursos")
        semaphore.release()

        # Simular tiempo de espera
        tiempo_espera = random.randint(1, 3)
        print(f"Thread {thread_id}: Realizando trabajo...")
        time.sleep(tiempo_espera)

        # Devolver recursos
        semaphore.acquire()
        cantidad_recursos += cantidad_consumir
        print(f"Thread {thread_id}: Devolvió {cantidad_consumir} recursos")
        semaphore.release()

# Crear y ejecutar los threads
num_threads = 3

threads = []
for i in range(num_threads):
    t = threading.Thread(target=consumir_recurso, args=(i,))
    threads.append(t)
    t.start()

# Esperar a que todos los threads terminen
for t in threads:
    t.join()

print("Programa principal ha terminado")
