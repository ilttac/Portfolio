#include "CBullet.h"
#include "Global.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACBullet::ACBullet()
{
	Collision = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Collision;

	Collision->InitSphereRadius(5.0f);
	Collision->BodyInstance.SetCollisionProfileName("Projectile");
	Collision->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	Collision->CanCharacterStepUpOn = ECB_No;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Collision);
	Mesh->SetRelativeLocation(FVector(0, 0, 0));
	Mesh->SetRelativeRotation(FRotator(90, -90, 0));
	Mesh->SetRelativeScale3D(FVector(5, 5, 5));

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	Projectile->UpdatedComponent = Collision;
	Projectile->InitialSpeed = 12000.0f;
	Projectile->MaxSpeed = 15000.0f;
	Projectile->bInitialVelocityInLocalSpace = true;
	Projectile->bRotationFollowsVelocity = false;
	Projectile->bShouldBounce = false;
	InitialLifeSpan = 1.0f;
	
	FString path = L"";
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>("TrailParticle");
	TrailParticle->SetupAttachment(RootComponent);

	TrailParticle->bAutoActivate = true;
	path = L"ParticleSystem'/Game/SciFiWeapLight/FX/Particles/P_AssaultRifle_Tracer_Light.P_AssaultRifle_Tracer_Light'";
	ConstructorHelpers::FObjectFinder<UParticleSystem> trailParticle(*path);
	if (trailParticle.Succeeded())
		TrailParticle->SetTemplate(trailParticle.Object);



}

void ACBullet::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentHit.AddDynamic(this, &ACBullet::OnHit);
	
}

void ACBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	CLog::Print(FString("Hit"));
	if (OtherActor == NULL) return;
	if (OtherActor == this) return;
	Destroy();
	if (OtherComp->IsSimulatingPhysics() == false) return;

	FString name = OtherActor->GetName();
	if (name.Contains("Floor") == true) return;
	
	//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	
}
void ACBullet::SetProjectileVelocity(FVector SrcVec)
{
	RetNull(Projectile);
	
	Projectile->Velocity = SrcVec;
}


