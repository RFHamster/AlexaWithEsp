package com.robotica.bloqueadorAutomotivo.services;

import java.util.List;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.robotica.bloqueadorAutomotivo.entities.Consulta;
import com.robotica.bloqueadorAutomotivo.entities.User;
import com.robotica.bloqueadorAutomotivo.repositories.ConsultaRepository;

@Service
public class ConsultaService {
	@Autowired
	UserService userService;
	@Autowired
	private ConsultaRepository repository;
	
	public List<Consulta> findAll(){
		return repository.findAll();
	}
	
	public Consulta saveConsulta(Long user, String mensagem, String data){
		return repository.save(new Consulta(null, mensagem, data, userService.findById(user)));
	}
	
	public Consulta findByIdUsuario(Long id){
		return repository.findByUsuario(userService.findById(id));
	}
	
	public Consulta findByUsuario(User user){
		return repository.findByUsuario(user);
	}
	
	public Consulta findById(Long id) {
		Optional<Consulta> obj = repository.findById(id);
		return obj.get();
	}
}
