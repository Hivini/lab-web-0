<script lang="ts">
  import { onMount } from 'svelte';

  import {
    Col,
    Container,
    Row,
    Button,
    ListGroup,
    ListGroupItem,
    Modal,
    ModalBody,
    ModalFooter,
    ModalHeader,
    Input,
    Label,
  } from 'sveltestrap';

  let open = false;
  let tasks = [];
  let loading = false;
  let title = '';

  const toggle = () => {
    open = !open;
    title = '';
  };

  onMount(async () => {
    getTasks();
  });

  function getTasks() {
    loading = true;
    fetch('https://6122ae2fd446280017054916.mockapi.io/todos')
      .then((response) => response.json())
      .then((data) => {
        console.log(data);
        loading = false;
        tasks = data;
      })
      .catch((error) => {
        console.log(error);
        return [];
      });
  }

  function finishTask(id){
	const task = tasks.find(d => d.id === id);
	task.finished = true;
	console.log(tasks);
  }

  function deleteTask(id) {
    tasks = tasks.filter((d) => d.id !== id);
  }

  function addTask() {
    tasks = [{title}, ...tasks];
	console.log(tasks);
    toggle();
  }
</script>

<main>
  <Container>
    <h1>To Do List</h1>
    <Row>
      <Col xs="12" style="text-align: right;"
        ><Button outline color="primary" on:click={toggle}>Agregar Tarea</Button
        ></Col
      >
    </Row>
    <Row style="margin-top: 16px;">
      <Col>
        <ListGroup>
          {#each tasks as task}
            <ListGroupItem  color="{task.finished === true ? 'success' : ''}">
              <div>
                {task.title}
                <div style="float: right;">
                  <Button disabled={task.finished} color="primary" size="sm" on:click={() => task.finished = true}>Terminar</Button>
                  <Button
                    color="danger"
                    size="sm"
                    on:click={() => deleteTask(task.id)}>Borrar</Button
                  >
                </div>
              </div></ListGroupItem
            >
          {/each}
        </ListGroup>
      </Col>
    </Row>
  </Container>

  <Modal isOpen={open} {toggle}>
    <ModalHeader {toggle}>Agregar Tarea</ModalHeader>
    <ModalBody>
      <Label for="title">Titulo</Label>
      <Input
        bind:value={title}
        type="text"
        name="title"
        id="title"
        placeholder="Titulo"
      />
    </ModalBody>
    <ModalFooter>
      <Button color="danger" on:click={toggle}>Cancelar</Button>
      <Button color="primary" on:click={addTask}>Agregar Tarea</Button>
    </ModalFooter>
  </Modal>
</main>

<style>
	.finished{
		background-color: rgb(72, 141, 72);
	}
</style>
