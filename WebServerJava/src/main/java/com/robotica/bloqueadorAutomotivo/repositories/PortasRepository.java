package com.robotica.bloqueadorAutomotivo.repositories;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import com.robotica.bloqueadorAutomotivo.entities.Portas;

public interface PortasRepository extends JpaRepository<Portas,Long>{
	@Query(value = "SELECT c FROM Portas c WHERE c.chassi = :chassi")
	List<Portas> findByChassi(Integer chassi);
}
