# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I.
LDFLAGS = 
LIBS = 

# Fichiers sources et objets
SRCS = \
    ChargeurFormatJson.cpp \
    ChargeurFormatTexte.cpp \
    ChargeurInteraction.cpp \
    Case.cpp \
    Grille.cpp \
    SolveurKakuro.cpp \
    UtilitaireSolveur.cpp \
    main.cpp

OBJS = $(SRCS:.cpp=.o)
EXEC = kakuro_solver

# Règle par défaut
all: $(EXEC)

# Lien des objets pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Règle générique pour compiler les .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(EXEC)

# Pour une utilisation avec nlohmann/json (si nécessaire)
# Assurez-vous que json.hpp est dans votre include path# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I. -g -DDEBUG
LDFLAGS = 
LIBS = -lpthread -ldl

# Fichiers sources et objets
SRCS = \
    ChargeurFormatJson.cpp \
    ChargeurFormatTexte.cpp \
    ChargeurInteraction.cpp \
    Case.cpp \
    Grille.cpp \
    SolveurKakuro.cpp \
    UtilitaireSolveur.cpp \
    main.cpp \
    Logger.cpp

OBJS = $(SRCS:.cpp=.o)
EXEC = kakuro_solver

# Règle par défaut
all: $(EXEC)

# Lien des objets pour créer l'exécutable
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

# Règle générique pour compiler les .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS) $(EXEC)

