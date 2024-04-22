package com.robotica.bloqueadorAutomotivo.entities;

import java.util.Objects;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class Portas {
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Long id;
	private String nome;
	private String tipo;
	private String porta;
	private Integer chassi;
	
	public Portas() {}
	
	public Portas(Long id, String nome, String tipo, String porta, Integer chassi) {
		this.id = id;
		this.nome = nome;
		this.tipo = tipo;
		this.porta = porta;
		this.chassi = chassi;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getTipo() {
		return tipo;
	}

	public void setTipo(String tipo) {
		this.tipo = tipo;
	}

	public String getPorta() {
		return porta;
	}

	public void setPorta(String porta) {
		this.porta = porta;
	}

	public Integer getChassi() {
		return chassi;
	}

	public void setChassi(Integer chassi) {
		this.chassi = chassi;
	}

	public Long getId() {
		return id;
	}

	@Override
	public int hashCode() {
		return Objects.hash(chassi, id, nome, porta, tipo);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Portas other = (Portas) obj;
		return Objects.equals(chassi, other.chassi) && Objects.equals(id, other.id) && Objects.equals(nome, other.nome)
				&& Objects.equals(porta, other.porta) && Objects.equals(tipo, other.tipo);
	}
	
	
	
	
}
