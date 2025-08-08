import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

let scene, camera, renderer, mesh;
let clock = new THREE.Clock();

function init() {
  // Scene & Camera
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 0.1, 1000);
  camera.position.set(0, 70, 100);
  camera.lookAt(0, 0, 0);

  //Get header height
  const header = document.querySelector(".header");
  const headerHeight = header.clientHeight;
  const headerWidth = header.clientWidth;



  // Renderer
  renderer = new THREE.WebGLRenderer({ canvas:document.getElementById("headBG"), antialias: true });
  renderer.setSize(headerWidth, headerHeight);
  renderer.setClearColor(0x000000); // black
  document.body.appendChild(renderer.domElement);


  // Plane Geometry
  const geometry = new THREE.PlaneGeometry(100, 100, 30, 30);
  geometry.rotateX(-Math.PI / 2); // rotate to be horizontal

  // Material
  const material = new THREE.MeshBasicMaterial({
    color: 0xBFBFBF,
    wireframe: true,
    transparent: true,
    opacity: 0.2
  });

  // Mesh
  mesh = new THREE.Mesh(geometry, material);
  scene.add(mesh);

  // Optional controls (mouse orbit)
  const controls = new OrbitControls(camera, renderer.domElement);
  controls.enableDamping = true;
  controls.dampingFactor = 0.1;
}

function animate() {
  requestAnimationFrame(animate);

  let time = clock.getElapsedTime();
  // Displace vertices with sine noise
  mesh.geometry.verticesNeedUpdate = true;
  const pos = mesh.geometry.attributes.position;
  for (let i = 0; i < pos.count; i++) {
    const x = pos.getX(i);
    const y = pos.getY(i);
    const z = pos.getZ(i);
    const wave = Math.sin(x * 0.2 + time) * Math.cos(z * 0.2 + time) * 8;
    pos.setY(i, wave);
  }
  pos.needsUpdate = true;

  renderer.render(scene, camera);
}

window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

init();
animate();
