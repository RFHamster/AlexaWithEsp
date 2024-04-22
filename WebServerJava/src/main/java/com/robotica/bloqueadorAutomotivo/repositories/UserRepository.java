package com.robotica.bloqueadorAutomotivo.repositories;

import org.springframework.data.jpa.repository.JpaRepository;

import com.robotica.bloqueadorAutomotivo.entities.User;

public interface UserRepository extends JpaRepository<User,Long>{
	User findByUsuario(String usuario);
}
