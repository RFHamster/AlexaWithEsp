package com.robotica.bloqueadorAutomotivo.entities;

import java.util.Objects;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

@Entity
@Table(name="tb_consulta")
public class Consulta {

	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	private Long id;
	private String mensagem;
	private String dataConsulta;
	@ManyToOne
	@JoinColumn(name="user_id", nullable=false)
	private User userId;
	
	public Consulta(Long id, String mensagem, String dataConsulta, User usuarioConsulta) {
		this.id = id;
		this.mensagem = mensagem;
		this.dataConsulta = dataConsulta;
		this.userId = usuarioConsulta;
	}
	
	public Consulta() {}
	
	
	public Long getId() {
		return id;
	}
	
	public User getUserId() {
		return userId;
	}

	public void setUserId(User usuarioConsulta) {
		this.userId = usuarioConsulta;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getMensagem() {
		return mensagem;
	}

	public void setMensagem(String mensagem) {
		this.mensagem = mensagem;
	}

	public String getDataConsulta() {
		return dataConsulta;
	}

	public void setDataConsulta(String dataConsulta) {
		this.dataConsulta = dataConsulta;
	}

	@Override
	public int hashCode() {
		return Objects.hash(dataConsulta, mensagem);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Consulta other = (Consulta) obj;
		return Objects.equals(dataConsulta, other.dataConsulta) && Objects.equals(mensagem, other.mensagem);
	}
	
	
}
