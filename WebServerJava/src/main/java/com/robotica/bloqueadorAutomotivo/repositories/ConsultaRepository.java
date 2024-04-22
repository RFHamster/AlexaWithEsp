package com.robotica.bloqueadorAutomotivo.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import com.robotica.bloqueadorAutomotivo.entities.Consulta;
import com.robotica.bloqueadorAutomotivo.entities.User;

public interface ConsultaRepository extends JpaRepository<Consulta,Long>{
	@Query(value = "SELECT c FROM Consulta c WHERE c.userId = :userId")
	Consulta findByUsuario(User userId);
}
