from flask import Flask, request, jsonify
import sqlite3

conn = sqlite3.connect('p.db')

# Exclui a tabela se ela já existir
conn.execute('''DROP TABLE IF EXISTS portas''')

# Cria a tabela
conn.execute('''CREATE TABLE portas (
                chassi INT,
                nome VARCHAR(255) PRIMARY KEY,
                porta VARCHAR(50),
                tipo VARCHAR(50)
            );''')

app = Flask(__name__)

@app.route('/registrar', methods=['GET'])
def registrar_porta():
    # Recebe todos os atributos da tabela por um GET
    chassi = request.args.get('chassi')
    nome = request.args.get('nome')
    porta = request.args.get('porta')
    tipo = request.args.get('tipo')

    # Verifica se a porta já existe para este chassi e nome
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM portas WHERE chassi=? AND nome=?", (chassi, nome))
    porta_existente = cursor.fetchone()

    if porta_existente:
        # Se a porta já existe, exclui ela
        conn.execute("DELETE FROM portas WHERE chassi=? AND nome=?", (chassi, nome))
        conn.commit()
        print(f"Porta existente excluída: {porta_existente}")
    
    # Insere a nova porta
    conn.execute("INSERT INTO portas (chassi, nome, porta, tipo) VALUES (?, ?, ?, ?)", (chassi, nome, porta, tipo))
    conn.commit()
    print(f"Nova porta adicionada: ({chassi}, {nome}, {porta}, {tipo})")

    return jsonify({"mensagem": "Porta registrada com sucesso."})

@app.route('/recuperar', methods=['GET'])
def recuperar_portas():
    # Recebe um chassi
    chassi = request.args.get('chassi')

    # Retorna todas as portas atreladas ao chassi
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM portas WHERE chassi=?", (chassi))
    portas = cursor.fetchall()

    if not portas:
        return jsonify({"mensagem": "Nenhuma porta encontrada para este chassi."}), 404
    else:
        portas_json = [{"nome": porta[1], "porta": porta[2], "tipo": porta[3]} for porta in portas]
        return jsonify(portas_json)

@app.route('/portas', methods=['GET'])
def verificar_chassi():
    chassi = request.args.get('chassi')

    if chassi == "1":
        return jsonify({"mensagem": "Ok"})
    else:
        return jsonify({"mensagem": "Tente novamente"})

if __name__ == '__main__':
    app.run(debug=True)