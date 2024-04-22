package com.robotica.bloqueadorAutomotivo.services;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.robotica.bloqueadorAutomotivo.entities.Portas;
import com.robotica.bloqueadorAutomotivo.repositories.PortasRepository;

@Service
public class PortasService {
	@Autowired
	private PortasRepository repository;
	
	public List<Portas> findAll(){
		return repository.findAll();
	}
	
	public Portas savePortas(String nome, String tipo, String porta, Integer chassi){
		return repository.save(new Portas(null, nome, tipo, porta, chassi));
	}
	
	public List<Portas> findByIdChassi(Integer id){
		return repository.findByChassi(id);
	}
	
}
