package com.robotica.bloqueadorAutomotivo.config;

import java.util.Arrays;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Profile;

import com.robotica.bloqueadorAutomotivo.entities.Consulta;
import com.robotica.bloqueadorAutomotivo.entities.User;
import com.robotica.bloqueadorAutomotivo.repositories.ConsultaRepository;
import com.robotica.bloqueadorAutomotivo.repositories.UserRepository;


@Configuration
@Profile("test")
public class TestConfig implements CommandLineRunner{
	@Autowired
	UserRepository userRepository;
	@Autowired
	ConsultaRepository consultaRepository;
	@Override
	public void run(String... args) throws Exception {
		List<User> users = Arrays.asList(
	            new User(null,"RFHamster", "123456", "Rhuan"),
	            new User(null,"mayaraAmarela", "senha123", "Mayara"),
	            new User(null,"gabiDoFrifas", "password", "Gabriela")
	        );
		Consulta consulta = new Consulta(null, "L2", "12/04/2004", users.get(0));

        userRepository.saveAll(users);
        consultaRepository.save(consulta);
	}

}