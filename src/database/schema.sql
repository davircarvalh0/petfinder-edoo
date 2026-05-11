PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS pessoas (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tipo TEXT NOT NULL CHECK (tipo IN ('dono', 'usuario')),
    nome TEXT NOT NULL,
    cpf TEXT UNIQUE,
    telefone TEXT,
    email TEXT UNIQUE, 
    usuario TEXT UNIQUE NOT NULL,
    senha TEXT NOT NULL, 
    endereco TEXT,
    data_cadastro TEXT DEFAULT (datetime('now', 'localtime')),
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    atualizado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime'))
);

CREATE TABLE IF NOT EXISTS animais (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    dono_id INTEGER NOT NULL,
    tipo TEXT NOT NULL CHECK (tipo IN ('cachorro', 'gato')),
    nome TEXT NOT NULL,
    peso REAL,
    idade INTEGER,
    cor TEXT,
    raca TEXT,
    foto TEXT,
    porte TEXT,
    usa_coleira INTEGER CHECK (usa_coleira IN (0, 1)),
    pelagem TEXT,
    eh_castrado INTEGER CHECK (eh_castrado IN (0, 1)),
    localizacao TEXT, 
    descricao TEXT,   
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    atualizado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    FOREIGN KEY (dono_id) REFERENCES pessoas(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS localizacoes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    latitude REAL,
    longitude REAL,
    bairro TEXT NOT NULL,
    referencia TEXT,
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime'))
);

CREATE TABLE IF NOT EXISTS ocorrencias (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    animal_id INTEGER NOT NULL,
    data_desaparecimento TEXT NOT NULL,
    ultima_localizacao_id INTEGER,
    status TEXT NOT NULL DEFAULT 'perdido' CHECK (status IN ('perdido', 'encontrado')),
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    atualizado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    FOREIGN KEY (animal_id) REFERENCES animais(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (ultima_localizacao_id) REFERENCES localizacoes(id) ON UPDATE CASCADE ON DELETE SET NULL
);

CREATE TABLE IF NOT EXISTS avistamentos (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    usuario_id INTEGER NOT NULL,
    ocorrencia_id INTEGER NOT NULL,
    localizacao_id INTEGER NOT NULL,
    data_avistamento TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    descricao TEXT,
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    FOREIGN KEY (usuario_id) REFERENCES pessoas(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (ocorrencia_id) REFERENCES ocorrencias(id) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (localizacao_id) REFERENCES localizacoes(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS pontos_resgate (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    telefone TEXT,
    localizacao_id INTEGER NOT NULL,
    tipo TEXT,
    criado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    atualizado_em TEXT NOT NULL DEFAULT (datetime('now', 'localtime')),
    FOREIGN KEY (localizacao_id) REFERENCES localizacoes(id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_pessoas_tipo ON pessoas(tipo);
CREATE INDEX IF NOT EXISTS idx_animais_dono ON animais(dono_id);
CREATE INDEX IF NOT EXISTS idx_animais_tipo ON animais(tipo);
CREATE INDEX IF NOT EXISTS idx_ocorrencias_animal ON ocorrencias(animal_id);
CREATE INDEX IF NOT EXISTS idx_ocorrencias_status ON ocorrencias(status);
CREATE INDEX IF NOT EXISTS idx_avistamentos_usuario ON avistamentos(usuario_id);
CREATE INDEX IF NOT EXISTS idx_avistamentos_ocorrencia ON avistamentos(ocorrencia_id);
CREATE INDEX IF NOT EXISTS idx_localizacoes_bairro ON localizacoes(bairro);
